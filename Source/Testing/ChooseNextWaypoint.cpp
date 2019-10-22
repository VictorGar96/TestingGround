// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingGuard.h" // Remove
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // TODO protect pointers

    /* Get Patrol Points
    */
    auto AIController = OwnerComp.GetAIOwner();
    auto ControlledPawn = AIController->GetPawn();
    auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
    auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

    /** Set next waypoint
    */
    auto BlackBoardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackBoardComp->GetValueAsInt(IndexKey.SelectedKeyName);

    if (PatrolPoints[Index] != nullptr)
        BlackBoardComp->SetValueAsObject(WayPointKey.SelectedKeyName, PatrolPoints[Index]);
    else
        return EBTNodeResult::Failed;


    /** Cycle Index
    */
    auto NextIndex = (Index + 1) % PatrolPoints.Num();
    BlackBoardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

    UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);

    
    return EBTNodeResult::Succeeded;
}
