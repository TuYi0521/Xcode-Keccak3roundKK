#!/bin/bash
for i in {21..63}
do
echo "$i"
./forwardCollisionSearch KK3RoundTrailCore/KK1600-$i > collisionSearchLog$i.txt&
#./trailCoreForwardExtension > testHistory.txt
done
