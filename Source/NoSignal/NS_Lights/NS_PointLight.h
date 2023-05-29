#pragma once

#include "NS_Light.h"
#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "NS_PointLight.generated.h"

UCLASS()
class NOSIGNAL_API ANS_PointLight : public ANS_Light
{
	GENERATED_BODY()

public:
	ANS_PointLight();

protected:
	virtual bool IsInSightOfPlayer(FHitResult& OutHit) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPointLightComponent* PointLight;
};
