[big brain](https://content.vexrobotics.com/docs/21-22/tipping-point/GameManual-2.1.pdf)
![[Skills.png]]
![[Pasted image 20211120005327.png]]
![[Pasted image 20211120005515.png]]
Auton:
(left) race forward and grab neutral mogo, turn slightly more than 90 degrees to the left so track is facing the middle, vacuum the middle rings while ramming the other mogos to get them onto our side (actually it should be either reach the mogo in front and slightly turn or drift, drift sounds cooler)
~~turn less than 90 degrees to push middle and end neutral to our side~~
(right) grab awp mogo vacuum up the L-shape rings, we theoretically could disregard the awp mogo and just use a neutral one as scoring if we are confident our alliance won't be able to get the awp point for us (we should focus more on auton bonus than awp)

(both) barely return past the midline because that's all we need, make sure to move at max speed because even if we don't get the points, at least deny opponents points, end goal is the try to get auton bonus. we want a strong enough auton so that we don't really have to focus on scoring in manual and instead on sabo

remember, we have 3 preloads so to score those we can just grab the neutral and run the track for the full 15 sec to ensure nothing gets stuck.

Automations:
Vacuum - make a script that can grab the mogo, then "vacuum" up rings on the floor and immediately score it on the pole
Rage quit - i doubt we could make this work but like it would be really funny if we could make a mechanism to flip over the other robots (not sure this legal though)


Manual:
the main idea behind points is that because goals and balancing gain a significantly more amount of points than rings we should focus on goals, but don't disregard the donuts. by using the vacuum method we are able to focus on keeping goals while sucking donuts as a byproduct of just moving around
Anchoring - drive up the platform to place the mogo instead of just placing it if the mogo has donuts
we should try to get the first mogo that has donuts on the platform first to "secure" it (yes ik they still can mess it up)
after auton the main focus is just keeping the mogos with us, if we put the neutrals on our platform, while they can still tilt it off, it'll be harder for them the actually take it. auton should give us a big enough advantage so that manual should just be sabotage and protecting what we already have

Sabotage:
because we probably won't be able to score a ton of points based on the design of our bot, the main strategy is just deny points from the opponents
steal - because alliance mogos on the right side get 20 points it should be easy to yionk those near neutral
flip - flip over opponent mogos that have donuts because it eliminates those points, additionally makes it harder to pick up/move
tilt - if a mogo with donuts is near the edge of the platform, tilt the platform with the arm (or 4 bar) to push it off

rough outline for timeline:
**keynote: hoarding is allowed but only one at a time**(unclear if it means one per bot or total) we could use this as a "protection" mechanism
total = 1:45
auton -> try to get mogos somewhat on our side and score the initial points

first 30 -> we have early advantage of neutral mogos which means we should capitalize, try to get at least 2 neutral mogos on the platform (preferrably with a few donuts in each), we want to secure the neutrals first because they can give opponents points while alliance mogos can't so its more ok if we lose those

middle 45 -> main cause of disruption for opponents and try to collect donuts in alliance goals in the meantime. so something like secure the 2 neutrals on the platform from before then run around with the other 2 alliance mogos and collect donuts while disrupting the opponents

last 30 **keynote here: cannot touch opponent platforms** -> try to sabotage on the field or collect donuts, there's not much that can be done here if the steps below were executed properly, most important thing here would probably be protect the alliance mogos

this might be kinda a stretch but this would be best case scenario: squeeze 2 small neutrals onto the platform with a few donuts, then grab the 2 alliance mogos and hop onto the platform (`4*40+2*30+1*(base donuts)+3*(branch donuts) = ggez`) remember, the platform (and subsequently anything touching it) is considered invincible so mogos will be the gg factor

last key point to the driver/spotter, it's a lot more effective to destroy something nicely done than to prevent them from making it in the first place, ie flip over a fat mogo instead of trying to steal donuts and push mogos off platform instead of trying to stop opponent from putting it on there, because we can spend the in between time doing something more productive