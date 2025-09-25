#pragma once

#include "CoreMinimal.h"
#include "SimpleVRFeatureKitType.generated.h"

class IVRGrabInterface;
class UMotionControllerComponent;

UENUM(BlueprintType)
enum class EVRItemObjectState : uint8
{
	VR_DRAG_FREE UMETA(DisplayName = "Free"),
	VR_DRAG_BUSY UMETA(DisplayName = "Busy"),
	VR_DRAG_MAX  UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class EGrabType :uint8
{
	GRAB_FREE		UMETA(DisplayName = "Free"),
	GRAB_SNAP		UMETA(DisplayName = "Snap"),
	GRAB_RELEASE	UMETA(DisplayName = "Snap and release"),
};

UENUM(BlueprintType)
enum class EGrabTrackingType :uint8
{
	GRAB_NONE			UMETA(DisplayName = "None"),
	GRAB_LEFT			UMETA(DisplayName = "Left"),
	GRAB_RIGHT			UMETA(DisplayName = "Right"),
	GRAB_GUN			UMETA(DisplayName = "Gun"),
	GRAB_PAD			UMETA(DisplayName = "Pad"),
	GRAB_EXTERNALCAMERA	UMETA(DisplayName = "External Camera"),
	GRAB_HMD			UMETA(DisplayName = "HMD"),
	GRAB_ANYTRACKING	UMETA(DisplayName = "Any Tracking"),
	GRAB_OTHERSPECIAL	UMETA(DisplayName = "Other Special"),
	GRAB_HAND_COUNT		UMETA(DisplayName = "Controller Hand Count"),
	GRAB_MAX			UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class EAttachInfoType :uint8
{
	ID_INVALID					UMETA(DisplayName = "ID invalid"),//无效ID
	INCORRECT_TYPE				UMETA(DisplayName = "type Error"),//类型错误
	PREPARING_INSTALLATION      UMETA(DisplayName = "Preparing Installation"),//准备安装
	INSTALLED					UMETA(DisplayName = "Installed"),//已经安装
	UNINSTALL					UMETA(DisplayName = "Uninstall"),//已经卸载
	ALREADY_EQUIPPED			UMETA(DisplayName = "Already Equipped"),//已经安装过
	MAX							UMETA(DisplayName = "Max"),
};

UENUM(BlueprintType)
enum class ESimpleGrabLockState :uint8
{
	GRABLOCK_NONE			UMETA(DisplayName = "NONE"),//默认状态
	GRABLOCK_TOUCH			UMETA(DisplayName = "Touch"),//碰到Grab碰撞体
	GRABLOCK_LOCK           UMETA(DisplayName = "Lock"),//已经拿捏
};

USTRUCT(BlueprintType, Blueprintable)
struct SIMPLEVRFEATUREKIT_API FSimpleGrabLockInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FSimpleGrabLockInfo();

	IVRGrabInterface* AGrabInterface;//AHand
	IVRGrabInterface* BGrabInterface;//BHand

	UPROPERTY()
	ESimpleGrabLockState GrabLockState;

public:

	void Clear();
	bool IsValid() const;
};

//主要链 以IK为主 以类人为主。也可以是狗，猫。四足动画，但是不适合蜈蚣，这种类型需要用户自定义
UENUM(BlueprintType)
enum class EMainTouchControlChain :uint8
{
	CONTROLCHAIN_HAND_R = 0		UMETA(DisplayName = "Hand Right"),//
	CONTROLCHAIN_HAND_L			UMETA(DisplayName = "Hand Left"),//
	CONTROLCHAIN_UPPERARM_L		UMETA(DisplayName = "Upperarm Left"),//
	CONTROLCHAIN_UPPERARM_R		UMETA(DisplayName = "Upperarm Right"),//
	CONTROLCHAIN_LOWERARM_L		UMETA(DisplayName = "Lowerarm Left"),//
	CONTROLCHAIN_LOWERARM_R		UMETA(DisplayName = "Lowerarm Right"),//
	CONTROLCHAIN_SPINE_01		UMETA(DisplayName = "spine 01"),//
	CONTROLCHAIN_SPINE_02		UMETA(DisplayName = "spine 02"),//
	CONTROLCHAIN_SPINE_03		UMETA(DisplayName = "spine 03"),//
	CONTROLCHAIN_CALF_R			UMETA(DisplayName = "calf Right"),//
	CONTROLCHAIN_CALF_L			UMETA(DisplayName = "calf Left"),//
	CONTROLCHAIN_LEG_R			UMETA(DisplayName = "Leg Right"),//
	CONTROLCHAIN_LEG_L			UMETA(DisplayName = "Leg Left"),//
	CONTROLCHAIN_HEAD			UMETA(DisplayName = "Head"),//
	CONTROLCHAIN_PELVIS			UMETA(DisplayName = "Pelvis"),//
	CONTROLCHAIN_MAX										//									//
};

UENUM(BlueprintType)
enum class EIncrementSpringbackType :uint8
{
	CONTROLCHAIN_RESTORE			UMETA(DisplayName = "Restore"),// 还原到原来的位置
	CONTROLCHAIN_NO_RESTORE			UMETA(DisplayName = "No Restore"),// 不需要恢复
	CONTROLCHAIN_SPRING_RESTORE		UMETA(DisplayName = "Spring Restore"),// 按照弹簧的方式还原
};

UENUM(BlueprintType)
enum class EVRMovementMode :uint8
{
	VRM_CLIMB UMETA(DisplayName = "Climb"),
};

USTRUCT(BlueprintType, Blueprintable)
struct SIMPLEVRFEATUREKIT_API FSimpleTouchControlInfo
{
	GENERATED_USTRUCT_BODY()

	FSimpleTouchControlInfo();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	FName BoneName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	FVector InitializationPosition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	FRotator InitializationRotation;

	UPROPERTY()
	TWeakObjectPtr<USceneComponent> TouchController;

	FSimpleTouchControlIncremental *IncrementalPtr;
};

USTRUCT(BlueprintType, Blueprintable)
struct SIMPLEVRFEATUREKIT_API FSimpleTouchControlIncremental
{
	GENERATED_USTRUCT_BODY()

	FSimpleTouchControlIncremental();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Bone")
	FName MainBoneName;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FVector IncrementPosition;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	FRotator IncrementRotation;

	UPROPERTY(BlueprintReadOnly, Category = "Base")
	uint8 ReferenceCount;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limit")
	FRotator MaxRotation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limit")
	FRotator MinRotation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limit")
	FVector MaxPosition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Limit")
	FVector MinPosition;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "BonesName")
	TArray<FName> Bones;
};

USTRUCT(BlueprintType, Blueprintable)
struct SIMPLEVRFEATUREKIT_API FInsertExtractInfo
{
	GENERATED_USTRUCT_BODY()

	FInsertExtractInfo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	TWeakObjectPtr<UMotionControllerComponent> MotionControllerComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	TWeakObjectPtr<USceneComponent> AttachedComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	TWeakObjectPtr<USceneComponent> Hand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	FName AttachName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	FVector InsertDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	FVector Extend;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = InsertExtract)
	float LengthOffset;
};

USTRUCT(BlueprintType, Blueprintable)
struct SIMPLEVRFEATUREKIT_API FVRClimbInfo
{
	GENERATED_USTRUCT_BODY()

	FVRClimbInfo();

	UPROPERTY()
	int32 HandleID;

	UPROPERTY()
	TWeakObjectPtr<UMotionControllerComponent> MotionController;

	UPROPERTY()
	TWeakObjectPtr<AActor> Hand;

	UPROPERTY()
	TWeakObjectPtr<UPrimitiveComponent> ClimbObject;

	UPROPERTY()
	FTransform RelativeToHandTransform;
};

inline bool operator==(const FVRClimbInfo& L, const FVRClimbInfo& R)
{
	return
		L.HandleID == R.HandleID ||
		L.MotionController == R.MotionController ||
		L.Hand == R.Hand;
}

typedef int32 FTouchControlHandle;