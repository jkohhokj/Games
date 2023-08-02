# Skills
<p align="center"><b>Prog</b></p>

- [ ] prelim
- [ ] done


![[Skills.png]]
<p align="center"><b>AutonR</b></p>

- [x] prelim
- [ ] done

Black = forwards
White = backwards
Orange = ClampF
Green = 4Bar
![[autonR.png]]

<p align="center"><b>AutonL</b></p>

- [x] prelim
- [x] done

![[autonL.png]]




![[Pasted image 20220222130618.png]]
OR
![[Pasted image 20220222130525.png]]
if the tall mogo makes it too unstable
## 260 auton pathing

total of 5 cross lengths traveled and 3 transfers
transfers should take 5 sec max
cross lengths can take up to 10 sec which should make the time then

0
ClampB, lift up and drive with forklift to middle, lower 4 bar when driving if too unstable
turn 135 deg left and drive with 4bar to platform, microadjust
release first mogo and set up for transfer

10
transfer

15


20

30

40

50

60


Part 1 15s (2s to lift first, 8s at 40% to do traveling -> 4s at 80%, 2s to place, 2s to set up, 3s to transfer, 2s to place)
ClampB, lift up and drive with forklift to middle, lower 4 bar when driving if too unstable
turn 135 deg left and drive with 4bar to platform, microadjust
release first mogo and set up for transfer
transfer and place second on platform

Part 2 20s (3s to third, 4s to fourth, 6s back, 2s to place, 3s to transfer, 2s to place all at 100%)
drive with forklift to third mogo, lower 4bar when driving
avoid rings and pick up fourth mogo
drive back with 4bar front lifting up, avoid rings
release third mogo and set up for transfer
transfer and place fourth on platform

Part 3 10s (3s to fifth, 7s to sixth)
drive with 4bar at an angle to fifth then clamp
drive back to sixth and forklift, perhaps use wall to help

Part 4 15s (3s to seventh, 2s to plat, 2s to place, 3s to transfer, 2s to place)
push bot tall seventh, 4bar up after that
stack fifth and set up for transfer
transfer and stack sixth

```cpp
// Part 1
// clamp and 4bar up
spinDriveMotorsRL(-.8,.8,30);
spinDriveMotorsRL(48/13.35,48/13.35,100);
// lower 4bar
// fk up
spinDriveMotorsRL(1.2,-1.2,30);
// raise 4bar
spinDriveMotorsRL(-50/13.35,-50/13.35,30);
spinDriveMotorsRL(0,-.4,30);
// place and adjust
spinDriveMotorsRL(3/13.35,3/13.35,60);
spinDriveMotorsRL(-.8,.8,30); //try combining with arc shit?
transfer();
spinDriveMotorsRL(-.8,.8,30);
// place and adjust


// Part 2
```

- [ ] derivative shit for pid
- [ ] add self correcting threads
- [ ] prolly throw in some motion tracking
- [ ] add voltage processing
- [ ] motor efficiency/temp
- [ ] log voltage maybe
- [ ] arc movement if there's time