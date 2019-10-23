// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWayPoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // TODO protect pointers



    /** Get Patrol Route
    */
    auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

    if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

    auto PatrolPoints = PatrolRoute->GetPatrolPoints();
    if (PatrolPoints.Num() == 0) 
    { 
        UE_LOG(LogTemp, Warning, TEXT("A guard is missing Patrol Points"));
        return EBTNodeResult::Failed;
    }

    /** Set next waypoint
    */
    auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    BlackBoardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);


    /** Cycle Index
    */
    auto NextIndex = (Index + 1) % PatrolPoints.Num();
    BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

    UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);
    
    return EBTNodeResult::Failed;
}
