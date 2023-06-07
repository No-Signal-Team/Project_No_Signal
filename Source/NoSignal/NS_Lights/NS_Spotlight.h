#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NS_Light.h"
#include "Components/SpotLightComponent.h"
#include "NS_Spotlight.generated.h"

UCLASS()
class NOSIGNAL_API ANS_Spotlight : public ANS_Light
{
	GENERATED_BODY()

public:
	ANS_Spotlight();

	USpotLightComponent* GetSpotlightComponent() const { return Spotlight; }

protected:
	virtual bool IsInSightOfPlayer(FHitResult& OutHit) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USpotLightComponent* Spotlight;
};
