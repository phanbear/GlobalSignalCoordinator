#include "abstractstatemachinebasis.h"

AbstractStateMachineBasis::AbstractStateMachineBasis(QObject *parent) : QObject(parent)
{

}

void AbstractStateMachineBasis::pushAGlobalSignalIntoPrioritizedBuffer(const GlobalSignal &aGlobalSignal)
{
    if (prioritizedBuffer.contains(aGlobalSignal.Priority))
    {
        prioritizedBuffer[aGlobalSignal.Priority].append(aGlobalSignal);
    }
    else
    {
        prioritizedBuffer.insert(aGlobalSignal.Priority, QList<GlobalSignal>({aGlobalSignal}));
    }
    deleteEmptyListsFromPrioritizedBuffer();
}

void AbstractStateMachineBasis::deleteEmptyListsFromPrioritizedBuffer()
{
    while (prioritizedBuffer.size())
    {
        if (prioritizedBuffer.last().size())
            break;
        else
        {
            prioritizedBuffer.remove(prioritizedBuffer.lastKey());
        }
    }
}

void AbstractStateMachineBasis::clearPrioritizedBuffer()
{
    if (prioritizedBuffer.size())
        prioritizedBuffer.clear();
}

GlobalSignal AbstractStateMachineBasis::popMostPrioritizedGlobalSignalOutOfPrioritizedBuffer()
{
    GlobalSignal tmpReturn = prioritizedBuffer.last().takeFirst();
    deleteEmptyListsFromPrioritizedBuffer();
    return tmpReturn;
}
