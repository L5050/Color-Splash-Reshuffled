[SharedConstants]
moduleMatches = 0x7467d6cf

.origin = codecave

_damageFunc:
.ptr 0x0213c1e8

_healthBuff:
.float 0.3

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


0x0213dd14 = b _moreDamage
0x0218801c = nop
0x0221249c = b _patchPaintedItems
0x02475650 = blr
