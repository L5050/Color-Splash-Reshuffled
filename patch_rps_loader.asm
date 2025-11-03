[SharedConstants]
moduleMatches = 0x7467d6cf

.origin = codecave

_damageFunc:
.ptr 0x0213c1e8

_levelFunc:
.ptr 0x02211b08

_healthBuff:
.float 0.3

_fixSoftlock:
.float 1.0

_speedBuff:
.float 0.85

_moreDamage:
mflr r5
lis r4, _damageFunc@ha
lwz r4, _damageFunc@l(r4)
cmpw CR0, r4, r5
bne _isEnemy
li r4, 0x0
lis r5, _healthBuff@ha
lfs f3, _healthBuff@l(r5)
fmuls f10, f10, f3
fsubs f29, f29, f10
li r5, 0x0
b 0x213dd18

_isEnemy:
li r4, 0x0
li r5, 0x0
fadd f10, f10, f10
lis r5, _fixSoftlock@ha
lfs f3, _fixSoftlock@l(r5)
fsubs f10, f10, f3
fsubs f29, f29, f10
b 0x213dd18

_collectCard:
b 0x0220d648

_cancelCollectCard2:
addi r4, r4, -0x94
b _collectCard

_cancelCollectCard:
cmpwi r4, 0x12b
ble _cancelCollectCard2
b _collectCard

_patchPaintedItems:
cmpwi r4, 0xf3
bge _cancelCollectCard
b _collectCard

_patchLevelUps:
add r0, r12, r3
li r3, 0x1E
add r0, r0, r3
b 0x02211b08

_handleKamek:
cmplwi r0, 0x3
blt _handleKamekDisappear
li r0, 0x5
stw r0, 0x1d10(r31)
b 0x0218b138

_handleKamekDisappear:
li r0, 0x2
stw r0, 0x1d10(r31)
b 0x0218b138

_patchMarioSpeed:
lis r5, _speedBuff@ha
lfs f2, _speedBuff@l(r5)
b 0x0220b07c

0x0218fbf8 = bl _handleKamek
0x0213dd14 = b _moreDamage
0x0218801c = nop
0x0221249c = b _patchPaintedItems
0x02475650 = blr
0x02211b04 = b _patchLevelUps
0x0220b078 = b _patchMarioSpeed
