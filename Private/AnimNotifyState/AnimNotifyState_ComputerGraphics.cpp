//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_ComputerGraphics.h"
#include "SimpleComboType.h"
#include "GameFramework/Character.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"

#if WITH_EDITOR
#include "AnimationEditorPreviewActor.h"
#endif

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

UAnimNotifyState_ComputerGraphics::UAnimNotifyState_ComputerGraphics()
	:bControllerRotation(false)
	,bPlayCameraAnim(false)
{
	FieldOfView = 90.0f;
	AspectRatio = 1.777778f;
	OrthoWidth = 512.0f;
	OrthoNearClipPlane = 0.0f;
	OrthoFarClipPlane = WORLD_MAX;
	bConstrainAspectRatio = false;
	bUseFieldOfViewForLOD = true;
	PostProcessBlendWeight = 1.0f;
	ProjectionMode = ECameraProjectionMode::Perspective;
	CharacterRotatorOffset.Yaw = -90.f;

	ComputerGraphicsType = ESimpleDrawComputerGraphicsType::DRAWDEBUGTRACE_NONE;
	CGMixingEffectType = ESimpleDrawCGMixingEffectType::DRAWDEBUGTRACE_NOT_MIXED_OUT;

	bDrawDebug = false;
}

void UAnimNotifyState_ComputerGraphics::NotifyBegin(
	USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, 
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AActor *InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{	
		if (!InCharacter->GetWorld()->IsNetMode(ENetMode::NM_DedicatedServer))
		{
#if WITH_EDITOR
			if (AAnimationEditorPreviewActor* InEPActor = Cast<AAnimationEditorPreviewActor>(InCharacter))
			{
				//FRotator InActorRotation = InEPActor->GetActorRotation();
				//InActorRotation.Yaw = -90.f;

				InEPActor->SetActorRotation(CharacterRotatorOffset);
			}
#endif

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			auto CamaraPos = MeshComp->GetComponentTransform().TransformPosition(RelativePos);

			auto NewRot = Rotation;
			if (!bControllerRotation)
			{
				auto ViewPos = CameraViewOffsetValue + MeshComp->GetComponentLocation();
				NewRot = FRotationMatrix::MakeFromX(ViewPos - CamaraPos).Rotator();
			}
			//ASceneCapture2D
			if (ACameraActor* InCamera = InCharacter->GetWorld()->SpawnActor<ACameraActor>(
				ACameraActor::StaticClass(),
				CamaraPos,
				NewRot, SpawnParameters))
			{
				InCamera->SetLifeSpan(TotalDuration);

				InCamera->GetCameraComponent()->SetFieldOfView(FieldOfView);
				InCamera->GetCameraComponent()->SetOrthoWidth(OrthoWidth);
				InCamera->GetCameraComponent()->SetOrthoNearClipPlane(OrthoNearClipPlane);
				InCamera->GetCameraComponent()->SetOrthoFarClipPlane(OrthoFarClipPlane);
				InCamera->GetCameraComponent()->SetAspectRatio(AspectRatio);
				InCamera->GetCameraComponent()->SetConstraintAspectRatio(bConstrainAspectRatio);
				InCamera->GetCameraComponent()->SetUseFieldOfViewForLOD(bUseFieldOfViewForLOD);
				InCamera->GetCameraComponent()->SetProjectionMode(ProjectionMode.GetValue());
				InCamera->GetCameraComponent()->PostProcessSettings = PostProcessSettings;

				if (ACharacter* InMyCharacter = Cast<ACharacter>(InCharacter))
				{
					if (APlayerController* InController = GetPlayerController(InMyCharacter))
					{
						InController->SetViewTargetWithBlend(InCamera,
							bPlayCameraAnim ? TotalDuration : 0.f);
					}
				}

				ViewObject = InCamera;
			}
		}
	}
}

void UAnimNotifyState_ComputerGraphics::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime,EventReference);

	if (ViewObject.IsValid())
	{
		if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
		{
#if WITH_EDITOR
			if (AAnimationEditorPreviewActor* InEPActor = Cast<AAnimationEditorPreviewActor>(InCharacter))
			{
				//FRotator InActorRotation = InEPActor->GetActorRotation();
				//InActorRotation.Yaw = -90.f;

				InEPActor->SetActorRotation(CharacterRotatorOffset);
			}
#endif
			if (ComputerGraphicsType == ESimpleDrawComputerGraphicsType::DRAWDEBUGTRACE_TRACK)
			{
				auto CamaraPos = MeshComp->GetComponentTransform().TransformPosition(RelativePos);

				auto NewRot = Rotation;
				if (!bControllerRotation)
				{
					auto ViewPos = CameraViewOffsetValue + MeshComp->GetComponentLocation();
					NewRot = FRotationMatrix::MakeFromX(ViewPos - CamaraPos).Rotator();
				}

				ViewObject->SetActorLocation(CamaraPos);
				ViewObject->SetActorRotation(NewRot);
			}
			
			if (ACameraActor* InCameraActor = Cast<ACameraActor>(ViewObject.Get()))
			{
				InCameraActor->GetCameraComponent()->SetFieldOfView(FieldOfView);
				InCameraActor->GetCameraComponent()->SetOrthoWidth(OrthoWidth);
				InCameraActor->GetCameraComponent()->SetOrthoNearClipPlane(OrthoNearClipPlane);
				InCameraActor->GetCameraComponent()->SetOrthoFarClipPlane(OrthoFarClipPlane);
				InCameraActor->GetCameraComponent()->SetAspectRatio(AspectRatio);
				InCameraActor->GetCameraComponent()->SetConstraintAspectRatio(bConstrainAspectRatio);
				InCameraActor->GetCameraComponent()->SetUseFieldOfViewForLOD(bUseFieldOfViewForLOD);
				InCameraActor->GetCameraComponent()->SetProjectionMode(ProjectionMode.GetValue());
				InCameraActor->GetCameraComponent()->PostProcessSettings = PostProcessSettings;

				if (bDrawDebug)
				{
					FVector ViewTarget = InCameraActor->GetActorRotation().Vector();
					ViewTarget.Normalize();

					float InDistance = FVector::Distance(
						InCameraActor->GetActorLocation(),
						MeshComp->GetComponentLocation());

					//绘制视觉中心
					DrawDebugLine(
						InCharacter->GetWorld(),
						InCameraActor->GetActorLocation(),
						(ViewTarget * InDistance) + InCameraActor->GetActorLocation(),
						FColor::Yellow, false,
						FrameDeltaTime * 2.f);

					//绘制角色移动路径
					DrawDebugLine(
						InCharacter->GetWorld(),
						FVector::ZeroVector,
						InCharacter->GetActorLocation(), 
						FColor::Red, false,
						FrameDeltaTime * 2.f);

					//绘制角色前进方向
					DrawDebugDirectionalArrow(
						InCharacter->GetWorld(),
						InCharacter->GetActorLocation(),
						InCharacter->GetActorForwardVector() * 200.f + InCharacter->GetActorLocation(),
						5.f,
						FColor::Green, 
						false,
						FrameDeltaTime * 2.f);

					if (UCameraComponent* CameraComponent = InCameraActor->GetCameraComponent())
					{
						float FOV = CameraComponent->FieldOfView * 0.5f;
						float NearClip = 0.1f;
						float FarClip = InDistance;

						// 获取相机的宽高比
						float InAspectRatio = CameraComponent->AspectRatio;

						// 相机的局部空间的近裁面和远裁面的高度和宽度
						float NearHeight = 2.0f * FMath::Tan(FMath::DegreesToRadians(FOV) * 0.5f) * NearClip;
						float NearWidth = NearHeight * InAspectRatio;

						float FarHeight = 2.0f * FMath::Tan(FMath::DegreesToRadians(FOV) * 0.5f) * FarClip;
						float FarWidth = FarHeight * InAspectRatio;

						// 定义相机局部空间的8个顶点
						FVector NearTopLeft(-NearWidth / 2, NearClip, NearHeight / 2);
						FVector NearTopRight(NearWidth / 2, NearClip, NearHeight / 2);
						FVector NearBottomLeft(-NearWidth / 2, NearClip, -NearHeight / 2);
						FVector NearBottomRight(NearWidth / 2, NearClip, -NearHeight / 2);

						FVector FarTopLeft(-FarWidth / 2, FarClip, FarHeight / 2);
						FVector FarTopRight(FarWidth / 2, FarClip, FarHeight / 2);
						FVector FarBottomLeft(-FarWidth / 2, FarClip, -FarHeight / 2);
						FVector FarBottomRight(FarWidth / 2, FarClip, -FarHeight / 2);

						// 获取相机的变换矩阵
						FTransform CameraTransform = CameraComponent->GetComponentTransform();

						//yaw旋转90
						CameraTransform.SetRotation(CameraTransform.GetRotation() * FRotator(0.f, -90.f, 0.f).Quaternion());

						// 将这些顶点变换到世界空间
						FVector WorldNearTopLeft = CameraTransform.TransformPosition(NearTopLeft);
						FVector WorldNearTopRight = CameraTransform.TransformPosition(NearTopRight);
						FVector WorldNearBottomLeft = CameraTransform.TransformPosition(NearBottomLeft);
						FVector WorldNearBottomRight = CameraTransform.TransformPosition(NearBottomRight);

						FVector WorldFarTopLeft = CameraTransform.TransformPosition(FarTopLeft);
						FVector WorldFarTopRight = CameraTransform.TransformPosition(FarTopRight);
						FVector WorldFarBottomLeft = CameraTransform.TransformPosition(FarBottomLeft);
						FVector WorldFarBottomRight = CameraTransform.TransformPosition(FarBottomRight);

						FColor Color = FColor::Yellow;
						FColor FarColor = FColor::Red;

						float Thickness = 1.f;
						float ViewLiftTime = FrameDeltaTime * 2.f;

						// 使用 DrawDebugLine 绘制视锥体
						DrawDebugLine(InCharacter->GetWorld(), WorldNearTopLeft, WorldFarTopLeft, Color, false, ViewLiftTime, 0, Thickness);
						DrawDebugLine(InCharacter->GetWorld(), WorldNearTopRight, WorldFarTopRight, Color, false, ViewLiftTime, 0, Thickness);
						DrawDebugLine(InCharacter->GetWorld(), WorldNearBottomLeft, WorldFarBottomLeft, Color, false, ViewLiftTime, 0, Thickness);
						DrawDebugLine(InCharacter->GetWorld(), WorldNearBottomRight, WorldFarBottomRight, Color, false, ViewLiftTime, 0, Thickness);

						DrawDebugLine(InCharacter->GetWorld(), WorldNearTopLeft, WorldNearTopRight, Color, false, ViewLiftTime, 0, Thickness);
						DrawDebugLine(InCharacter->GetWorld(), WorldNearBottomLeft, WorldNearBottomRight, Color, false, ViewLiftTime, 0, Thickness);
						DrawDebugLine(InCharacter->GetWorld(), WorldNearTopLeft, WorldNearBottomLeft, Color, false, ViewLiftTime, 0, Thickness);
						DrawDebugLine(InCharacter->GetWorld(), WorldNearTopRight, WorldNearBottomRight, Color, false, ViewLiftTime, 0, Thickness);

						DrawDebugLine(InCharacter->GetWorld(), WorldFarTopLeft, WorldFarTopRight, FarColor, false, ViewLiftTime, 0, Thickness * 4.f);
						DrawDebugLine(InCharacter->GetWorld(), WorldFarBottomLeft, WorldFarBottomRight, FarColor, false, ViewLiftTime, 0, Thickness * 4.f);
						DrawDebugLine(InCharacter->GetWorld(), WorldFarTopLeft, WorldFarBottomLeft, FarColor, false, ViewLiftTime, 0, Thickness * 4.f);
						DrawDebugLine(InCharacter->GetWorld(), WorldFarTopRight, WorldFarBottomRight, FarColor, false, ViewLiftTime, 0, Thickness * 4.f);

						//// 使用自定义的视场角和剪裁平面，生成一个放大的视锥体
						//FMatrix ProjectionMatrix = FReversedZPerspectiveMatrix(
						//	InCameraComponent->FieldOfView * (float)PI / 360.0f,  // 视场角转换为弧度
						//	InCameraComponent->AspectRatio,      // 宽高比
						//	0.1f,                  // 自定义近剪裁平面
						//	5000.f);                   // 自定

						//	FMatrix ViewMatrix = InCameraComponent->GetComponentTransform().ToInverseMatrixWithScale();
						//	FMatrix FrustumToWorld = ViewMatrix.InverseFast() * ProjectionMatrix.InverseFast();
						//	
						//	//绘制锥形状
						//	DrawDebugFrustum(
						//		InCharacter->GetWorld(),
						//		FrustumToWorld,
						//		FColor::Yellow,
						//		false,
						//		FrameDeltaTime * 2.f);

						/*DrawDebugCamera(InCharacter->GetWorld(),
							ViewObject->GetActorLocation(),
							ViewObject->GetActorRotation(),
							InCameraActor->GetCameraComponent()->FieldOfView,
							2.f,
							FColor::Yellow);*/
					}
				}
			}
		}	
	}
}

void UAnimNotifyState_ComputerGraphics::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation,EventReference);

	if (CGMixingEffectType != ESimpleDrawCGMixingEffectType::DRAWDEBUGTRACE_NOT_MIXED_OUT)
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
		{
			if (!InCharacter->GetWorld()->IsNetMode(ENetMode::NM_DedicatedServer))
			{
				if (APlayerController* InController = GetPlayerController(InCharacter))
				{
					float InValue = 0.f;
					if (CGMixingEffectType == ESimpleDrawCGMixingEffectType::DRAWDEBUGTRACE_GRADIENT_MIXED_OUT)
					{
						InValue = 1.f;
					}

					InController->SetViewTargetWithBlend(InController->GetPawn(), InValue);
				}
			}
		}
	}
}

APlayerController* UAnimNotifyState_ComputerGraphics::GetPlayerController(ACharacter* InCharacter) const
{
	if (InCharacter)
	{
		if (IsLocallyInputControlled(InCharacter))
		{
			return Cast<APlayerController>(InCharacter->GetController());
		}
		else
		{
			return InCharacter->GetWorld()->GetFirstPlayerController();
		}
	}

	return nullptr;
}

bool UAnimNotifyState_ComputerGraphics::IsLocallyInputControlled(ACharacter* InCharacter) const
{
	if (!InCharacter->IsNetMode(ENetMode::NM_DedicatedServer))
	{
		if (InCharacter->IsNetMode(ENetMode::NM_Standalone))
		{
			//不考虑分屏的情况
			if (InCharacter == InCharacter->GetWorld()->GetFirstPlayerController()->GetPawn())
			{
				return true;
			}
		}
		else if (InCharacter->IsNetMode(ENetMode::NM_ListenServer))
		{
			if (InCharacter == InCharacter->GetWorld()->GetFirstPlayerController()->GetPawn())
			{
				return true;
			}
		}
		else if (InCharacter->IsNetMode(ENetMode::NM_Client))
		{
			if (InCharacter->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
			{
				return true;
			}
		}
	}

	return false;
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif