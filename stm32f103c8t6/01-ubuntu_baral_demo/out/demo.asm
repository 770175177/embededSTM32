
out/demo.elf:     file format elf32-littlearm


Disassembly of section .text:

0800010c <memset>:
 800010c:	b570      	push	{r4, r5, r6, lr}
 800010e:	0786      	lsls	r6, r0, #30
 8000110:	d047      	beq.n	80001a2 <memset+0x96>
 8000112:	1e54      	subs	r4, r2, #1
 8000114:	2a00      	cmp	r2, #0
 8000116:	d03e      	beq.n	8000196 <memset+0x8a>
 8000118:	4603      	mov	r3, r0
 800011a:	b2ca      	uxtb	r2, r1
 800011c:	e001      	b.n	8000122 <memset+0x16>
 800011e:	3c01      	subs	r4, #1
 8000120:	d339      	bcc.n	8000196 <memset+0x8a>
 8000122:	f803 2b01 	strb.w	r2, [r3], #1
 8000126:	079d      	lsls	r5, r3, #30
 8000128:	d1f9      	bne.n	800011e <memset+0x12>
 800012a:	2c03      	cmp	r4, #3
 800012c:	d92c      	bls.n	8000188 <memset+0x7c>
 800012e:	b2cd      	uxtb	r5, r1
 8000130:	eb05 2505 	add.w	r5, r5, r5, lsl #8
 8000134:	2c0f      	cmp	r4, #15
 8000136:	461a      	mov	r2, r3
 8000138:	eb05 4505 	add.w	r5, r5, r5, lsl #16
 800013c:	d934      	bls.n	80001a8 <memset+0x9c>
 800013e:	f1a4 0c10 	sub.w	ip, r4, #16
 8000142:	f02c 060f 	bic.w	r6, ip, #15
 8000146:	f103 0e10 	add.w	lr, r3, #16
 800014a:	44b6      	add	lr, r6
 800014c:	ea4f 1c1c 	mov.w	ip, ip, lsr #4
 8000150:	e9c2 5500 	strd	r5, r5, [r2]
 8000154:	e9c2 5502 	strd	r5, r5, [r2, #8]
 8000158:	3210      	adds	r2, #16
 800015a:	4572      	cmp	r2, lr
 800015c:	d1f8      	bne.n	8000150 <memset+0x44>
 800015e:	f10c 0201 	add.w	r2, ip, #1
 8000162:	f014 0f0c 	tst.w	r4, #12
 8000166:	eb03 1202 	add.w	r2, r3, r2, lsl #4
 800016a:	f004 0c0f 	and.w	ip, r4, #15
 800016e:	d013      	beq.n	8000198 <memset+0x8c>
 8000170:	f1ac 0304 	sub.w	r3, ip, #4
 8000174:	f023 0303 	bic.w	r3, r3, #3
 8000178:	3304      	adds	r3, #4
 800017a:	4413      	add	r3, r2
 800017c:	f842 5b04 	str.w	r5, [r2], #4
 8000180:	4293      	cmp	r3, r2
 8000182:	d1fb      	bne.n	800017c <memset+0x70>
 8000184:	f00c 0403 	and.w	r4, ip, #3
 8000188:	b12c      	cbz	r4, 8000196 <memset+0x8a>
 800018a:	b2c9      	uxtb	r1, r1
 800018c:	441c      	add	r4, r3
 800018e:	f803 1b01 	strb.w	r1, [r3], #1
 8000192:	42a3      	cmp	r3, r4
 8000194:	d1fb      	bne.n	800018e <memset+0x82>
 8000196:	bd70      	pop	{r4, r5, r6, pc}
 8000198:	4664      	mov	r4, ip
 800019a:	4613      	mov	r3, r2
 800019c:	2c00      	cmp	r4, #0
 800019e:	d1f4      	bne.n	800018a <memset+0x7e>
 80001a0:	e7f9      	b.n	8000196 <memset+0x8a>
 80001a2:	4603      	mov	r3, r0
 80001a4:	4614      	mov	r4, r2
 80001a6:	e7c0      	b.n	800012a <memset+0x1e>
 80001a8:	46a4      	mov	ip, r4
 80001aa:	e7e1      	b.n	8000170 <memset+0x64>

080001ac <strlen>:
 80001ac:	f020 0103 	bic.w	r1, r0, #3
 80001b0:	f010 0003 	ands.w	r0, r0, #3
 80001b4:	f1c0 0000 	rsb	r0, r0, #0
 80001b8:	f851 3b04 	ldr.w	r3, [r1], #4
 80001bc:	f100 0c04 	add.w	ip, r0, #4
 80001c0:	ea4f 0ccc 	mov.w	ip, ip, lsl #3
 80001c4:	f06f 0200 	mvn.w	r2, #0
 80001c8:	bf1c      	itt	ne
 80001ca:	fa22 f20c 	lsrne.w	r2, r2, ip
 80001ce:	4313      	orrne	r3, r2
 80001d0:	f04f 0c01 	mov.w	ip, #1
 80001d4:	ea4c 2c0c 	orr.w	ip, ip, ip, lsl #8
 80001d8:	ea4c 4c0c 	orr.w	ip, ip, ip, lsl #16
 80001dc:	eba3 020c 	sub.w	r2, r3, ip
 80001e0:	ea22 0203 	bic.w	r2, r2, r3
 80001e4:	ea12 12cc 	ands.w	r2, r2, ip, lsl #7
 80001e8:	bf04      	itt	eq
 80001ea:	f851 3b04 	ldreq.w	r3, [r1], #4
 80001ee:	3004      	addeq	r0, #4
 80001f0:	d0f4      	beq.n	80001dc <strlen+0x30>
 80001f2:	f1c2 0100 	rsb	r1, r2, #0
 80001f6:	ea02 0201 	and.w	r2, r2, r1
 80001fa:	fab2 f282 	clz	r2, r2
 80001fe:	f1c2 021f 	rsb	r2, r2, #31
 8000202:	eb00 00d2 	add.w	r0, r0, r2, lsr #3
 8000206:	4770      	bx	lr

08000208 <SystemInit>:
 8000208:	4b37      	ldr	r3, [pc, #220]	@ (80002e8 <SystemInit+0xe0>)
 800020a:	b082      	sub	sp, #8
 800020c:	681a      	ldr	r2, [r3, #0]
 800020e:	f042 0201 	orr.w	r2, r2, #1
 8000212:	601a      	str	r2, [r3, #0]
 8000214:	6859      	ldr	r1, [r3, #4]
 8000216:	4a35      	ldr	r2, [pc, #212]	@ (80002ec <SystemInit+0xe4>)
 8000218:	400a      	ands	r2, r1
 800021a:	605a      	str	r2, [r3, #4]
 800021c:	681a      	ldr	r2, [r3, #0]
 800021e:	f022 7284 	bic.w	r2, r2, #17301504	@ 0x1080000
 8000222:	f422 3280 	bic.w	r2, r2, #65536	@ 0x10000
 8000226:	601a      	str	r2, [r3, #0]
 8000228:	681a      	ldr	r2, [r3, #0]
 800022a:	f422 2280 	bic.w	r2, r2, #262144	@ 0x40000
 800022e:	601a      	str	r2, [r3, #0]
 8000230:	685a      	ldr	r2, [r3, #4]
 8000232:	f422 02fe 	bic.w	r2, r2, #8323072	@ 0x7f0000
 8000236:	605a      	str	r2, [r3, #4]
 8000238:	f44f 021f 	mov.w	r2, #10420224	@ 0x9f0000
 800023c:	609a      	str	r2, [r3, #8]
 800023e:	2200      	movs	r2, #0
 8000240:	9200      	str	r2, [sp, #0]
 8000242:	9201      	str	r2, [sp, #4]
 8000244:	681a      	ldr	r2, [r3, #0]
 8000246:	f442 3280 	orr.w	r2, r2, #65536	@ 0x10000
 800024a:	601a      	str	r2, [r3, #0]
 800024c:	681a      	ldr	r2, [r3, #0]
 800024e:	f402 3200 	and.w	r2, r2, #131072	@ 0x20000
 8000252:	9201      	str	r2, [sp, #4]
 8000254:	9a00      	ldr	r2, [sp, #0]
 8000256:	3201      	adds	r2, #1
 8000258:	9200      	str	r2, [sp, #0]
 800025a:	9a01      	ldr	r2, [sp, #4]
 800025c:	b91a      	cbnz	r2, 8000266 <SystemInit+0x5e>
 800025e:	9a00      	ldr	r2, [sp, #0]
 8000260:	f5b2 6fa0 	cmp.w	r2, #1280	@ 0x500
 8000264:	d1f2      	bne.n	800024c <SystemInit+0x44>
 8000266:	681a      	ldr	r2, [r3, #0]
 8000268:	f412 3200 	ands.w	r2, r2, #131072	@ 0x20000
 800026c:	bf18      	it	ne
 800026e:	2201      	movne	r2, #1
 8000270:	9201      	str	r2, [sp, #4]
 8000272:	9a01      	ldr	r2, [sp, #4]
 8000274:	2a01      	cmp	r2, #1
 8000276:	d130      	bne.n	80002da <SystemInit+0xd2>
 8000278:	4a1d      	ldr	r2, [pc, #116]	@ (80002f0 <SystemInit+0xe8>)
 800027a:	6811      	ldr	r1, [r2, #0]
 800027c:	f041 0110 	orr.w	r1, r1, #16
 8000280:	6011      	str	r1, [r2, #0]
 8000282:	6811      	ldr	r1, [r2, #0]
 8000284:	f021 0103 	bic.w	r1, r1, #3
 8000288:	6011      	str	r1, [r2, #0]
 800028a:	6811      	ldr	r1, [r2, #0]
 800028c:	f041 0102 	orr.w	r1, r1, #2
 8000290:	6011      	str	r1, [r2, #0]
 8000292:	685a      	ldr	r2, [r3, #4]
 8000294:	605a      	str	r2, [r3, #4]
 8000296:	685a      	ldr	r2, [r3, #4]
 8000298:	605a      	str	r2, [r3, #4]
 800029a:	685a      	ldr	r2, [r3, #4]
 800029c:	f442 6280 	orr.w	r2, r2, #1024	@ 0x400
 80002a0:	605a      	str	r2, [r3, #4]
 80002a2:	685a      	ldr	r2, [r3, #4]
 80002a4:	f422 127c 	bic.w	r2, r2, #4128768	@ 0x3f0000
 80002a8:	605a      	str	r2, [r3, #4]
 80002aa:	685a      	ldr	r2, [r3, #4]
 80002ac:	f442 12e8 	orr.w	r2, r2, #1900544	@ 0x1d0000
 80002b0:	605a      	str	r2, [r3, #4]
 80002b2:	681a      	ldr	r2, [r3, #0]
 80002b4:	f042 7280 	orr.w	r2, r2, #16777216	@ 0x1000000
 80002b8:	601a      	str	r2, [r3, #0]
 80002ba:	681a      	ldr	r2, [r3, #0]
 80002bc:	0192      	lsls	r2, r2, #6
 80002be:	d5fc      	bpl.n	80002ba <SystemInit+0xb2>
 80002c0:	685a      	ldr	r2, [r3, #4]
 80002c2:	f022 0203 	bic.w	r2, r2, #3
 80002c6:	605a      	str	r2, [r3, #4]
 80002c8:	685a      	ldr	r2, [r3, #4]
 80002ca:	f042 0202 	orr.w	r2, r2, #2
 80002ce:	605a      	str	r2, [r3, #4]
 80002d0:	685a      	ldr	r2, [r3, #4]
 80002d2:	f002 020c 	and.w	r2, r2, #12
 80002d6:	2a08      	cmp	r2, #8
 80002d8:	d1fa      	bne.n	80002d0 <SystemInit+0xc8>
 80002da:	f04f 6200 	mov.w	r2, #134217728	@ 0x8000000
 80002de:	4b05      	ldr	r3, [pc, #20]	@ (80002f4 <SystemInit+0xec>)
 80002e0:	609a      	str	r2, [r3, #8]
 80002e2:	b002      	add	sp, #8
 80002e4:	4770      	bx	lr
 80002e6:	bf00      	nop
 80002e8:	40021000 	.word	0x40021000
 80002ec:	f8ff0000 	.word	0xf8ff0000
 80002f0:	40022000 	.word	0x40022000
 80002f4:	e000ed00 	.word	0xe000ed00

080002f8 <Reset_Handler>:
 80002f8:	2100      	movs	r1, #0
 80002fa:	e003      	b.n	8000304 <LoopCopyDataInit>

080002fc <CopyDataInit>:
 80002fc:	4b0a      	ldr	r3, [pc, #40]	@ (8000328 <LoopFillZerobss+0x10>)
 80002fe:	585b      	ldr	r3, [r3, r1]
 8000300:	5043      	str	r3, [r0, r1]
 8000302:	3104      	adds	r1, #4

08000304 <LoopCopyDataInit>:
 8000304:	4809      	ldr	r0, [pc, #36]	@ (800032c <LoopFillZerobss+0x14>)
 8000306:	4b0a      	ldr	r3, [pc, #40]	@ (8000330 <LoopFillZerobss+0x18>)
 8000308:	1842      	adds	r2, r0, r1
 800030a:	429a      	cmp	r2, r3
 800030c:	d3f6      	bcc.n	80002fc <CopyDataInit>
 800030e:	4a09      	ldr	r2, [pc, #36]	@ (8000334 <LoopFillZerobss+0x1c>)
 8000310:	e002      	b.n	8000318 <LoopFillZerobss>

08000312 <FillZerobss>:
 8000312:	2300      	movs	r3, #0
 8000314:	f842 3b04 	str.w	r3, [r2], #4

08000318 <LoopFillZerobss>:
 8000318:	4b07      	ldr	r3, [pc, #28]	@ (8000338 <LoopFillZerobss+0x20>)
 800031a:	429a      	cmp	r2, r3
 800031c:	d3f9      	bcc.n	8000312 <FillZerobss>
 800031e:	f7ff ff73 	bl	8000208 <SystemInit>
 8000322:	f000 fc65 	bl	8000bf0 <main>
 8000326:	4770      	bx	lr
 8000328:	08000f2b 	.word	0x08000f2b
 800032c:	20000000 	.word	0x20000000
 8000330:	20000004 	.word	0x20000004
 8000334:	20000004 	.word	0x20000004
 8000338:	20000118 	.word	0x20000118

0800033c <ADC1_2_IRQHandler>:
 800033c:	e7fe      	b.n	800033c <ADC1_2_IRQHandler>
	...

08000340 <NVIC_PriorityGroupConfig>:
 8000340:	4b03      	ldr	r3, [pc, #12]	@ (8000350 <NVIC_PriorityGroupConfig+0x10>)
 8000342:	f040 60bf 	orr.w	r0, r0, #100139008	@ 0x5f80000
 8000346:	f440 3000 	orr.w	r0, r0, #131072	@ 0x20000
 800034a:	60d8      	str	r0, [r3, #12]
 800034c:	4770      	bx	lr
 800034e:	bf00      	nop
 8000350:	e000ed00 	.word	0xe000ed00

08000354 <NVIC_Init>:
 8000354:	b570      	push	{r4, r5, r6, lr}
 8000356:	2501      	movs	r5, #1
 8000358:	7801      	ldrb	r1, [r0, #0]
 800035a:	f001 031f 	and.w	r3, r1, #31
 800035e:	409d      	lsls	r5, r3
 8000360:	78c3      	ldrb	r3, [r0, #3]
 8000362:	094c      	lsrs	r4, r1, #5
 8000364:	b1bb      	cbz	r3, 8000396 <NVIC_Init+0x42>
 8000366:	4b0e      	ldr	r3, [pc, #56]	@ (80003a0 <NVIC_Init+0x4c>)
 8000368:	7846      	ldrb	r6, [r0, #1]
 800036a:	68da      	ldr	r2, [r3, #12]
 800036c:	43d2      	mvns	r2, r2
 800036e:	f3c2 2202 	ubfx	r2, r2, #8, #3
 8000372:	f1c2 0304 	rsb	r3, r2, #4
 8000376:	409e      	lsls	r6, r3
 8000378:	7883      	ldrb	r3, [r0, #2]
 800037a:	200f      	movs	r0, #15
 800037c:	fa20 f202 	lsr.w	r2, r0, r2
 8000380:	4013      	ands	r3, r2
 8000382:	4333      	orrs	r3, r6
 8000384:	4a07      	ldr	r2, [pc, #28]	@ (80003a4 <NVIC_Init+0x50>)
 8000386:	011b      	lsls	r3, r3, #4
 8000388:	b2db      	uxtb	r3, r3
 800038a:	4411      	add	r1, r2
 800038c:	f881 3300 	strb.w	r3, [r1, #768]	@ 0x300
 8000390:	f842 5024 	str.w	r5, [r2, r4, lsl #2]
 8000394:	bd70      	pop	{r4, r5, r6, pc}
 8000396:	4b03      	ldr	r3, [pc, #12]	@ (80003a4 <NVIC_Init+0x50>)
 8000398:	3420      	adds	r4, #32
 800039a:	f843 5024 	str.w	r5, [r3, r4, lsl #2]
 800039e:	e7f9      	b.n	8000394 <NVIC_Init+0x40>
 80003a0:	e000ed00 	.word	0xe000ed00
 80003a4:	e000e100 	.word	0xe000e100

080003a8 <SysTick_CLKSourceConfig>:
 80003a8:	f04f 23e0 	mov.w	r3, #3758153728	@ 0xe000e000
 80003ac:	691a      	ldr	r2, [r3, #16]
 80003ae:	2804      	cmp	r0, #4
 80003b0:	bf0c      	ite	eq
 80003b2:	f042 0204 	orreq.w	r2, r2, #4
 80003b6:	f022 0204 	bicne.w	r2, r2, #4
 80003ba:	611a      	str	r2, [r3, #16]
 80003bc:	4770      	bx	lr

080003be <GPIO_Init>:
 80003be:	b5f0      	push	{r4, r5, r6, r7, lr}
 80003c0:	78cb      	ldrb	r3, [r1, #3]
 80003c2:	880e      	ldrh	r6, [r1, #0]
 80003c4:	06da      	lsls	r2, r3, #27
 80003c6:	bf48      	it	mi
 80003c8:	788a      	ldrbmi	r2, [r1, #2]
 80003ca:	f003 050f 	and.w	r5, r3, #15
 80003ce:	bf48      	it	mi
 80003d0:	4315      	orrmi	r5, r2
 80003d2:	780a      	ldrb	r2, [r1, #0]
 80003d4:	b1c2      	cbz	r2, 8000408 <GPIO_Init+0x4a>
 80003d6:	2100      	movs	r1, #0
 80003d8:	2701      	movs	r7, #1
 80003da:	f04f 0c0f 	mov.w	ip, #15
 80003de:	6802      	ldr	r2, [r0, #0]
 80003e0:	fa07 f401 	lsl.w	r4, r7, r1
 80003e4:	ea34 0e06 	bics.w	lr, r4, r6
 80003e8:	d10a      	bne.n	8000400 <GPIO_Init+0x42>
 80003ea:	2b28      	cmp	r3, #40	@ 0x28
 80003ec:	d129      	bne.n	8000442 <GPIO_Init+0x84>
 80003ee:	6144      	str	r4, [r0, #20]
 80003f0:	008c      	lsls	r4, r1, #2
 80003f2:	fa0c fe04 	lsl.w	lr, ip, r4
 80003f6:	ea22 020e 	bic.w	r2, r2, lr
 80003fa:	fa05 f404 	lsl.w	r4, r5, r4
 80003fe:	4322      	orrs	r2, r4
 8000400:	3101      	adds	r1, #1
 8000402:	2908      	cmp	r1, #8
 8000404:	d1ec      	bne.n	80003e0 <GPIO_Init+0x22>
 8000406:	6002      	str	r2, [r0, #0]
 8000408:	2eff      	cmp	r6, #255	@ 0xff
 800040a:	d919      	bls.n	8000440 <GPIO_Init+0x82>
 800040c:	2100      	movs	r1, #0
 800040e:	f04f 0c01 	mov.w	ip, #1
 8000412:	6842      	ldr	r2, [r0, #4]
 8000414:	f101 0408 	add.w	r4, r1, #8
 8000418:	fa0c f404 	lsl.w	r4, ip, r4
 800041c:	ea34 0706 	bics.w	r7, r4, r6
 8000420:	d10a      	bne.n	8000438 <GPIO_Init+0x7a>
 8000422:	2b28      	cmp	r3, #40	@ 0x28
 8000424:	d111      	bne.n	800044a <GPIO_Init+0x8c>
 8000426:	6144      	str	r4, [r0, #20]
 8000428:	270f      	movs	r7, #15
 800042a:	008c      	lsls	r4, r1, #2
 800042c:	40a7      	lsls	r7, r4
 800042e:	ea22 0207 	bic.w	r2, r2, r7
 8000432:	fa05 f404 	lsl.w	r4, r5, r4
 8000436:	4322      	orrs	r2, r4
 8000438:	3101      	adds	r1, #1
 800043a:	2908      	cmp	r1, #8
 800043c:	d1ea      	bne.n	8000414 <GPIO_Init+0x56>
 800043e:	6042      	str	r2, [r0, #4]
 8000440:	bdf0      	pop	{r4, r5, r6, r7, pc}
 8000442:	2b48      	cmp	r3, #72	@ 0x48
 8000444:	d1d4      	bne.n	80003f0 <GPIO_Init+0x32>
 8000446:	6104      	str	r4, [r0, #16]
 8000448:	e7d2      	b.n	80003f0 <GPIO_Init+0x32>
 800044a:	2b48      	cmp	r3, #72	@ 0x48
 800044c:	bf08      	it	eq
 800044e:	6104      	streq	r4, [r0, #16]
 8000450:	e7ea      	b.n	8000428 <GPIO_Init+0x6a>

08000452 <GPIO_SetBits>:
 8000452:	6101      	str	r1, [r0, #16]
 8000454:	4770      	bx	lr

08000456 <GPIO_ResetBits>:
 8000456:	6141      	str	r1, [r0, #20]
 8000458:	4770      	bx	lr
	...

0800045c <RCC_GetClocksFreq>:
 800045c:	4a1a      	ldr	r2, [pc, #104]	@ (80004c8 <RCC_GetClocksFreq+0x6c>)
 800045e:	b510      	push	{r4, lr}
 8000460:	6853      	ldr	r3, [r2, #4]
 8000462:	f003 030c 	and.w	r3, r3, #12
 8000466:	2b08      	cmp	r3, #8
 8000468:	d12c      	bne.n	80004c4 <RCC_GetClocksFreq+0x68>
 800046a:	6853      	ldr	r3, [r2, #4]
 800046c:	6851      	ldr	r1, [r2, #4]
 800046e:	f3c3 4383 	ubfx	r3, r3, #18, #4
 8000472:	03cc      	lsls	r4, r1, #15
 8000474:	f103 0302 	add.w	r3, r3, #2
 8000478:	d41f      	bmi.n	80004ba <RCC_GetClocksFreq+0x5e>
 800047a:	4914      	ldr	r1, [pc, #80]	@ (80004cc <RCC_GetClocksFreq+0x70>)
 800047c:	434b      	muls	r3, r1
 800047e:	6003      	str	r3, [r0, #0]
 8000480:	6851      	ldr	r1, [r2, #4]
 8000482:	4c13      	ldr	r4, [pc, #76]	@ (80004d0 <RCC_GetClocksFreq+0x74>)
 8000484:	f3c1 1103 	ubfx	r1, r1, #4, #4
 8000488:	5c61      	ldrb	r1, [r4, r1]
 800048a:	40cb      	lsrs	r3, r1
 800048c:	6043      	str	r3, [r0, #4]
 800048e:	6851      	ldr	r1, [r2, #4]
 8000490:	f3c1 2102 	ubfx	r1, r1, #8, #3
 8000494:	5c61      	ldrb	r1, [r4, r1]
 8000496:	fa23 f101 	lsr.w	r1, r3, r1
 800049a:	6081      	str	r1, [r0, #8]
 800049c:	6851      	ldr	r1, [r2, #4]
 800049e:	f3c1 21c2 	ubfx	r1, r1, #11, #3
 80004a2:	5c61      	ldrb	r1, [r4, r1]
 80004a4:	40cb      	lsrs	r3, r1
 80004a6:	60c3      	str	r3, [r0, #12]
 80004a8:	6852      	ldr	r2, [r2, #4]
 80004aa:	490a      	ldr	r1, [pc, #40]	@ (80004d4 <RCC_GetClocksFreq+0x78>)
 80004ac:	f3c2 3281 	ubfx	r2, r2, #14, #2
 80004b0:	5c8a      	ldrb	r2, [r1, r2]
 80004b2:	fbb3 f3f2 	udiv	r3, r3, r2
 80004b6:	6103      	str	r3, [r0, #16]
 80004b8:	bd10      	pop	{r4, pc}
 80004ba:	6851      	ldr	r1, [r2, #4]
 80004bc:	0389      	lsls	r1, r1, #14
 80004be:	d4dc      	bmi.n	800047a <RCC_GetClocksFreq+0x1e>
 80004c0:	4905      	ldr	r1, [pc, #20]	@ (80004d8 <RCC_GetClocksFreq+0x7c>)
 80004c2:	e7db      	b.n	800047c <RCC_GetClocksFreq+0x20>
 80004c4:	4b04      	ldr	r3, [pc, #16]	@ (80004d8 <RCC_GetClocksFreq+0x7c>)
 80004c6:	e7da      	b.n	800047e <RCC_GetClocksFreq+0x22>
 80004c8:	40021000 	.word	0x40021000
 80004cc:	003d0900 	.word	0x003d0900
 80004d0:	08000c54 	.word	0x08000c54
 80004d4:	08000c50 	.word	0x08000c50
 80004d8:	007a1200 	.word	0x007a1200

080004dc <RCC_APB2PeriphClockCmd>:
 80004dc:	4b04      	ldr	r3, [pc, #16]	@ (80004f0 <RCC_APB2PeriphClockCmd+0x14>)
 80004de:	699a      	ldr	r2, [r3, #24]
 80004e0:	b111      	cbz	r1, 80004e8 <RCC_APB2PeriphClockCmd+0xc>
 80004e2:	4302      	orrs	r2, r0
 80004e4:	619a      	str	r2, [r3, #24]
 80004e6:	4770      	bx	lr
 80004e8:	ea22 0200 	bic.w	r2, r2, r0
 80004ec:	e7fa      	b.n	80004e4 <RCC_APB2PeriphClockCmd+0x8>
 80004ee:	bf00      	nop
 80004f0:	40021000 	.word	0x40021000

080004f4 <USART_Init>:
 80004f4:	b530      	push	{r4, r5, lr}
 80004f6:	4604      	mov	r4, r0
 80004f8:	8a03      	ldrh	r3, [r0, #16]
 80004fa:	88ca      	ldrh	r2, [r1, #6]
 80004fc:	b29b      	uxth	r3, r3
 80004fe:	f423 5340 	bic.w	r3, r3, #12288	@ 0x3000
 8000502:	4313      	orrs	r3, r2
 8000504:	8203      	strh	r3, [r0, #16]
 8000506:	8983      	ldrh	r3, [r0, #12]
 8000508:	888a      	ldrh	r2, [r1, #4]
 800050a:	f423 53b0 	bic.w	r3, r3, #5632	@ 0x1600
 800050e:	f023 030c 	bic.w	r3, r3, #12
 8000512:	041b      	lsls	r3, r3, #16
 8000514:	0c1b      	lsrs	r3, r3, #16
 8000516:	4313      	orrs	r3, r2
 8000518:	890a      	ldrh	r2, [r1, #8]
 800051a:	b087      	sub	sp, #28
 800051c:	4313      	orrs	r3, r2
 800051e:	894a      	ldrh	r2, [r1, #10]
 8000520:	460d      	mov	r5, r1
 8000522:	4313      	orrs	r3, r2
 8000524:	b29b      	uxth	r3, r3
 8000526:	8183      	strh	r3, [r0, #12]
 8000528:	8a83      	ldrh	r3, [r0, #20]
 800052a:	898a      	ldrh	r2, [r1, #12]
 800052c:	b29b      	uxth	r3, r3
 800052e:	f423 7340 	bic.w	r3, r3, #768	@ 0x300
 8000532:	4313      	orrs	r3, r2
 8000534:	8283      	strh	r3, [r0, #20]
 8000536:	a801      	add	r0, sp, #4
 8000538:	f7ff ff90 	bl	800045c <RCC_GetClocksFreq>
 800053c:	e9dd 3203 	ldrd	r3, r2, [sp, #12]
 8000540:	4914      	ldr	r1, [pc, #80]	@ (8000594 <USART_Init+0xa0>)
 8000542:	428c      	cmp	r4, r1
 8000544:	bf08      	it	eq
 8000546:	4613      	moveq	r3, r2
 8000548:	2219      	movs	r2, #25
 800054a:	89a1      	ldrh	r1, [r4, #12]
 800054c:	4353      	muls	r3, r2
 800054e:	682a      	ldr	r2, [r5, #0]
 8000550:	040d      	lsls	r5, r1, #16
 8000552:	bf4c      	ite	mi
 8000554:	0052      	lslmi	r2, r2, #1
 8000556:	0092      	lslpl	r2, r2, #2
 8000558:	2164      	movs	r1, #100	@ 0x64
 800055a:	fbb3 f3f2 	udiv	r3, r3, r2
 800055e:	fbb3 f0f1 	udiv	r0, r3, r1
 8000562:	fb01 3310 	mls	r3, r1, r0, r3
 8000566:	0102      	lsls	r2, r0, #4
 8000568:	89a0      	ldrh	r0, [r4, #12]
 800056a:	0400      	lsls	r0, r0, #16
 800056c:	bf4b      	itete	mi
 800056e:	00db      	lslmi	r3, r3, #3
 8000570:	011b      	lslpl	r3, r3, #4
 8000572:	3332      	addmi	r3, #50	@ 0x32
 8000574:	3332      	addpl	r3, #50	@ 0x32
 8000576:	bf4b      	itete	mi
 8000578:	fbb3 f3f1 	udivmi	r3, r3, r1
 800057c:	fbb3 f3f1 	udivpl	r3, r3, r1
 8000580:	f003 0307 	andmi.w	r3, r3, #7
 8000584:	f003 030f 	andpl.w	r3, r3, #15
 8000588:	4313      	orrs	r3, r2
 800058a:	b29b      	uxth	r3, r3
 800058c:	8123      	strh	r3, [r4, #8]
 800058e:	b007      	add	sp, #28
 8000590:	bd30      	pop	{r4, r5, pc}
 8000592:	bf00      	nop
 8000594:	40013800 	.word	0x40013800

08000598 <USART_Cmd>:
 8000598:	8983      	ldrh	r3, [r0, #12]
 800059a:	b121      	cbz	r1, 80005a6 <USART_Cmd+0xe>
 800059c:	b29b      	uxth	r3, r3
 800059e:	f443 5300 	orr.w	r3, r3, #8192	@ 0x2000
 80005a2:	8183      	strh	r3, [r0, #12]
 80005a4:	4770      	bx	lr
 80005a6:	f423 5300 	bic.w	r3, r3, #8192	@ 0x2000
 80005aa:	041b      	lsls	r3, r3, #16
 80005ac:	0c1b      	lsrs	r3, r3, #16
 80005ae:	e7f8      	b.n	80005a2 <USART_Cmd+0xa>

080005b0 <USART_ITConfig>:
 80005b0:	2301      	movs	r3, #1
 80005b2:	b510      	push	{r4, lr}
 80005b4:	f3c1 1442 	ubfx	r4, r1, #5, #3
 80005b8:	2c01      	cmp	r4, #1
 80005ba:	f001 011f 	and.w	r1, r1, #31
 80005be:	fa03 f301 	lsl.w	r3, r3, r1
 80005c2:	d105      	bne.n	80005d0 <USART_ITConfig+0x20>
 80005c4:	300c      	adds	r0, #12
 80005c6:	b142      	cbz	r2, 80005da <USART_ITConfig+0x2a>
 80005c8:	6802      	ldr	r2, [r0, #0]
 80005ca:	4313      	orrs	r3, r2
 80005cc:	6003      	str	r3, [r0, #0]
 80005ce:	bd10      	pop	{r4, pc}
 80005d0:	2c02      	cmp	r4, #2
 80005d2:	bf0c      	ite	eq
 80005d4:	3010      	addeq	r0, #16
 80005d6:	3014      	addne	r0, #20
 80005d8:	e7f5      	b.n	80005c6 <USART_ITConfig+0x16>
 80005da:	6802      	ldr	r2, [r0, #0]
 80005dc:	ea22 0303 	bic.w	r3, r2, r3
 80005e0:	e7f4      	b.n	80005cc <USART_ITConfig+0x1c>

080005e2 <USART_ReceiveData>:
 80005e2:	8880      	ldrh	r0, [r0, #4]
 80005e4:	f3c0 0008 	ubfx	r0, r0, #0, #9
 80005e8:	4770      	bx	lr

080005ea <USART_GetITStatus>:
 80005ea:	4603      	mov	r3, r0
 80005ec:	2001      	movs	r0, #1
 80005ee:	f3c1 1242 	ubfx	r2, r1, #5, #3
 80005f2:	b510      	push	{r4, lr}
 80005f4:	2a01      	cmp	r2, #1
 80005f6:	f001 041f 	and.w	r4, r1, #31
 80005fa:	fa00 f004 	lsl.w	r0, r0, r4
 80005fe:	d10d      	bne.n	800061c <USART_GetITStatus+0x32>
 8000600:	899a      	ldrh	r2, [r3, #12]
 8000602:	b292      	uxth	r2, r2
 8000604:	4010      	ands	r0, r2
 8000606:	881a      	ldrh	r2, [r3, #0]
 8000608:	b292      	uxth	r2, r2
 800060a:	b130      	cbz	r0, 800061a <USART_GetITStatus+0x30>
 800060c:	2301      	movs	r3, #1
 800060e:	0a09      	lsrs	r1, r1, #8
 8000610:	408b      	lsls	r3, r1
 8000612:	421a      	tst	r2, r3
 8000614:	bf14      	ite	ne
 8000616:	2001      	movne	r0, #1
 8000618:	2000      	moveq	r0, #0
 800061a:	bd10      	pop	{r4, pc}
 800061c:	2a02      	cmp	r2, #2
 800061e:	bf0c      	ite	eq
 8000620:	8a1a      	ldrheq	r2, [r3, #16]
 8000622:	8a9a      	ldrhne	r2, [r3, #20]
 8000624:	e7ed      	b.n	8000602 <USART_GetITStatus+0x18>

08000626 <NMI_Handler>:
 8000626:	4770      	bx	lr

08000628 <HardFault_Handler>:
 8000628:	e7fe      	b.n	8000628 <HardFault_Handler>

0800062a <MemManage_Handler>:
 800062a:	e7fe      	b.n	800062a <MemManage_Handler>

0800062c <BusFault_Handler>:
 800062c:	e7fe      	b.n	800062c <BusFault_Handler>

0800062e <UsageFault_Handler>:
 800062e:	e7fe      	b.n	800062e <UsageFault_Handler>

08000630 <SVC_Handler>:
 8000630:	4770      	bx	lr

08000632 <DebugMon_Handler>:
 8000632:	4770      	bx	lr

08000634 <PendSV_Handler>:
 8000634:	4770      	bx	lr

08000636 <SysTick_Handler>:
 8000636:	4770      	bx	lr

08000638 <delay_init>:
 8000638:	b508      	push	{r3, lr}
 800063a:	f06f 0004 	mvn.w	r0, #4
 800063e:	f7ff feb3 	bl	80003a8 <SysTick_CLKSourceConfig>
 8000642:	4b08      	ldr	r3, [pc, #32]	@ (8000664 <delay_init+0x2c>)
 8000644:	4a08      	ldr	r2, [pc, #32]	@ (8000668 <delay_init+0x30>)
 8000646:	681b      	ldr	r3, [r3, #0]
 8000648:	fbb3 f3f2 	udiv	r3, r3, r2
 800064c:	4a07      	ldr	r2, [pc, #28]	@ (800066c <delay_init+0x34>)
 800064e:	b2db      	uxtb	r3, r3
 8000650:	7013      	strb	r3, [r2, #0]
 8000652:	ebc3 1243 	rsb	r2, r3, r3, lsl #5
 8000656:	eb03 0382 	add.w	r3, r3, r2, lsl #2
 800065a:	4a05      	ldr	r2, [pc, #20]	@ (8000670 <delay_init+0x38>)
 800065c:	00db      	lsls	r3, r3, #3
 800065e:	8013      	strh	r3, [r2, #0]
 8000660:	bd08      	pop	{r3, pc}
 8000662:	bf00      	nop
 8000664:	20000000 	.word	0x20000000
 8000668:	007a1200 	.word	0x007a1200
 800066c:	20000006 	.word	0x20000006
 8000670:	20000004 	.word	0x20000004

08000674 <delay_ms>:
 8000674:	4b0b      	ldr	r3, [pc, #44]	@ (80006a4 <delay_ms+0x30>)
 8000676:	2200      	movs	r2, #0
 8000678:	881b      	ldrh	r3, [r3, #0]
 800067a:	4358      	muls	r0, r3
 800067c:	f04f 23e0 	mov.w	r3, #3758153728	@ 0xe000e000
 8000680:	6158      	str	r0, [r3, #20]
 8000682:	619a      	str	r2, [r3, #24]
 8000684:	691a      	ldr	r2, [r3, #16]
 8000686:	f042 0201 	orr.w	r2, r2, #1
 800068a:	611a      	str	r2, [r3, #16]
 800068c:	691a      	ldr	r2, [r3, #16]
 800068e:	f002 1201 	and.w	r2, r2, #65537	@ 0x10001
 8000692:	2a01      	cmp	r2, #1
 8000694:	d0fa      	beq.n	800068c <delay_ms+0x18>
 8000696:	691a      	ldr	r2, [r3, #16]
 8000698:	f022 0201 	bic.w	r2, r2, #1
 800069c:	611a      	str	r2, [r3, #16]
 800069e:	2200      	movs	r2, #0
 80006a0:	619a      	str	r2, [r3, #24]
 80006a2:	4770      	bx	lr
 80006a4:	20000004 	.word	0x20000004

080006a8 <led_init>:
 80006a8:	b513      	push	{r0, r1, r4, lr}
 80006aa:	4c09      	ldr	r4, [pc, #36]	@ (80006d0 <led_init+0x28>)
 80006ac:	2101      	movs	r1, #1
 80006ae:	2010      	movs	r0, #16
 80006b0:	f7ff ff14 	bl	80004dc <RCC_APB2PeriphClockCmd>
 80006b4:	4b07      	ldr	r3, [pc, #28]	@ (80006d4 <led_init+0x2c>)
 80006b6:	4620      	mov	r0, r4
 80006b8:	a901      	add	r1, sp, #4
 80006ba:	9301      	str	r3, [sp, #4]
 80006bc:	f7ff fe7f 	bl	80003be <GPIO_Init>
 80006c0:	f44f 5100 	mov.w	r1, #8192	@ 0x2000
 80006c4:	4620      	mov	r0, r4
 80006c6:	f7ff fec4 	bl	8000452 <GPIO_SetBits>
 80006ca:	b002      	add	sp, #8
 80006cc:	bd10      	pop	{r4, pc}
 80006ce:	bf00      	nop
 80006d0:	40011000 	.word	0x40011000
 80006d4:	10032000 	.word	0x10032000

080006d8 <led_switch>:
 80006d8:	f44f 5100 	mov.w	r1, #8192	@ 0x2000
 80006dc:	b110      	cbz	r0, 80006e4 <led_switch+0xc>
 80006de:	4803      	ldr	r0, [pc, #12]	@ (80006ec <led_switch+0x14>)
 80006e0:	f7ff beb9 	b.w	8000456 <GPIO_ResetBits>
 80006e4:	4801      	ldr	r0, [pc, #4]	@ (80006ec <led_switch+0x14>)
 80006e6:	f7ff beb4 	b.w	8000452 <GPIO_SetBits>
 80006ea:	bf00      	nop
 80006ec:	40011000 	.word	0x40011000

080006f0 <usart_puts>:
 80006f0:	4603      	mov	r3, r0
 80006f2:	b510      	push	{r4, lr}
 80006f4:	4905      	ldr	r1, [pc, #20]	@ (800070c <usart_puts+0x1c>)
 80006f6:	461c      	mov	r4, r3
 80006f8:	f813 2b01 	ldrb.w	r2, [r3], #1
 80006fc:	b90a      	cbnz	r2, 8000702 <usart_puts+0x12>
 80006fe:	1a20      	subs	r0, r4, r0
 8000700:	bd10      	pop	{r4, pc}
 8000702:	880c      	ldrh	r4, [r1, #0]
 8000704:	0664      	lsls	r4, r4, #25
 8000706:	d5fc      	bpl.n	8000702 <usart_puts+0x12>
 8000708:	808a      	strh	r2, [r1, #4]
 800070a:	e7f4      	b.n	80006f6 <usart_puts+0x6>
 800070c:	40013800 	.word	0x40013800

08000710 <usart_gets>:
 8000710:	b5f7      	push	{r0, r1, r2, r4, r5, r6, r7, lr}
 8000712:	4605      	mov	r5, r0
 8000714:	2600      	movs	r6, #0
 8000716:	4f0e      	ldr	r7, [pc, #56]	@ (8000750 <usart_gets+0x40>)
 8000718:	4634      	mov	r4, r6
 800071a:	4638      	mov	r0, r7
 800071c:	4622      	mov	r2, r4
 800071e:	f10d 0107 	add.w	r1, sp, #7
 8000722:	3601      	adds	r6, #1
 8000724:	f000 fa42 	bl	8000bac <ring_buffer_peek>
 8000728:	b908      	cbnz	r0, 800072e <usart_gets+0x1e>
 800072a:	4604      	mov	r4, r0
 800072c:	e00a      	b.n	8000744 <usart_gets+0x34>
 800072e:	f89d 3007 	ldrb.w	r3, [sp, #7]
 8000732:	2b0d      	cmp	r3, #13
 8000734:	d109      	bne.n	800074a <usart_gets+0x3a>
 8000736:	4632      	mov	r2, r6
 8000738:	4629      	mov	r1, r5
 800073a:	4805      	ldr	r0, [pc, #20]	@ (8000750 <usart_gets+0x40>)
 800073c:	f000 fa20 	bl	8000b80 <ring_buffer_dequeue_arr>
 8000740:	2300      	movs	r3, #0
 8000742:	552b      	strb	r3, [r5, r4]
 8000744:	4620      	mov	r0, r4
 8000746:	b003      	add	sp, #12
 8000748:	bdf0      	pop	{r4, r5, r6, r7, pc}
 800074a:	2b0a      	cmp	r3, #10
 800074c:	d1e4      	bne.n	8000718 <usart_gets+0x8>
 800074e:	e7f2      	b.n	8000736 <usart_gets+0x26>
 8000750:	20000008 	.word	0x20000008

08000754 <usart_printf>:
 8000754:	b40f      	push	{r0, r1, r2, r3}
 8000756:	b500      	push	{lr}
 8000758:	b093      	sub	sp, #76	@ 0x4c
 800075a:	ab14      	add	r3, sp, #80	@ 0x50
 800075c:	f853 2b04 	ldr.w	r2, [r3], #4
 8000760:	2140      	movs	r1, #64	@ 0x40
 8000762:	a802      	add	r0, sp, #8
 8000764:	9301      	str	r3, [sp, #4]
 8000766:	f000 f9b9 	bl	8000adc <mini_vsnprintf>
 800076a:	a802      	add	r0, sp, #8
 800076c:	f7ff ffc0 	bl	80006f0 <usart_puts>
 8000770:	b013      	add	sp, #76	@ 0x4c
 8000772:	f85d eb04 	ldr.w	lr, [sp], #4
 8000776:	b004      	add	sp, #16
 8000778:	4770      	bx	lr
	...

0800077c <uart_init>:
 800077c:	b530      	push	{r4, r5, lr}
 800077e:	2101      	movs	r1, #1
 8000780:	b087      	sub	sp, #28
 8000782:	4604      	mov	r4, r0
 8000784:	4d1c      	ldr	r5, [pc, #112]	@ (80007f8 <uart_init+0x7c>)
 8000786:	f244 0004 	movw	r0, #16388	@ 0x4004
 800078a:	f7ff fea7 	bl	80004dc <RCC_APB2PeriphClockCmd>
 800078e:	4b1b      	ldr	r3, [pc, #108]	@ (80007fc <uart_init+0x80>)
 8000790:	4669      	mov	r1, sp
 8000792:	4628      	mov	r0, r5
 8000794:	9300      	str	r3, [sp, #0]
 8000796:	f7ff fe12 	bl	80003be <GPIO_Init>
 800079a:	f44f 6380 	mov.w	r3, #1024	@ 0x400
 800079e:	f8ad 3000 	strh.w	r3, [sp]
 80007a2:	2304      	movs	r3, #4
 80007a4:	4669      	mov	r1, sp
 80007a6:	4628      	mov	r0, r5
 80007a8:	f88d 3003 	strb.w	r3, [sp, #3]
 80007ac:	f7ff fe07 	bl	80003be <GPIO_Init>
 80007b0:	4b13      	ldr	r3, [pc, #76]	@ (8000800 <uart_init+0x84>)
 80007b2:	a801      	add	r0, sp, #4
 80007b4:	9301      	str	r3, [sp, #4]
 80007b6:	f7ff fdcd 	bl	8000354 <NVIC_Init>
 80007ba:	2300      	movs	r3, #0
 80007bc:	f44f 2240 	mov.w	r2, #786432	@ 0xc0000
 80007c0:	9402      	str	r4, [sp, #8]
 80007c2:	4c10      	ldr	r4, [pc, #64]	@ (8000804 <uart_init+0x88>)
 80007c4:	a902      	add	r1, sp, #8
 80007c6:	4620      	mov	r0, r4
 80007c8:	e9cd 3203 	strd	r3, r2, [sp, #12]
 80007cc:	f8ad 3014 	strh.w	r3, [sp, #20]
 80007d0:	f7ff fe90 	bl	80004f4 <USART_Init>
 80007d4:	2201      	movs	r2, #1
 80007d6:	4620      	mov	r0, r4
 80007d8:	f240 5125 	movw	r1, #1317	@ 0x525
 80007dc:	f7ff fee8 	bl	80005b0 <USART_ITConfig>
 80007e0:	4620      	mov	r0, r4
 80007e2:	2101      	movs	r1, #1
 80007e4:	f7ff fed8 	bl	8000598 <USART_Cmd>
 80007e8:	f44f 7280 	mov.w	r2, #256	@ 0x100
 80007ec:	4906      	ldr	r1, [pc, #24]	@ (8000808 <uart_init+0x8c>)
 80007ee:	4807      	ldr	r0, [pc, #28]	@ (800080c <uart_init+0x90>)
 80007f0:	f000 f99b 	bl	8000b2a <ring_buffer_init>
 80007f4:	b007      	add	sp, #28
 80007f6:	bd30      	pop	{r4, r5, pc}
 80007f8:	40010800 	.word	0x40010800
 80007fc:	18030200 	.word	0x18030200
 8000800:	01030325 	.word	0x01030325
 8000804:	40013800 	.word	0x40013800
 8000808:	20000018 	.word	0x20000018
 800080c:	20000008 	.word	0x20000008

08000810 <USART1_IRQHandler>:
 8000810:	b508      	push	{r3, lr}
 8000812:	f240 5125 	movw	r1, #1317	@ 0x525
 8000816:	4807      	ldr	r0, [pc, #28]	@ (8000834 <USART1_IRQHandler+0x24>)
 8000818:	f7ff fee7 	bl	80005ea <USART_GetITStatus>
 800081c:	b140      	cbz	r0, 8000830 <USART1_IRQHandler+0x20>
 800081e:	4805      	ldr	r0, [pc, #20]	@ (8000834 <USART1_IRQHandler+0x24>)
 8000820:	f7ff fedf 	bl	80005e2 <USART_ReceiveData>
 8000824:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
 8000828:	b2c1      	uxtb	r1, r0
 800082a:	4803      	ldr	r0, [pc, #12]	@ (8000838 <USART1_IRQHandler+0x28>)
 800082c:	f000 b984 	b.w	8000b38 <ring_buffer_queue>
 8000830:	bd08      	pop	{r3, pc}
 8000832:	bf00      	nop
 8000834:	40013800 	.word	0x40013800
 8000838:	20000008 	.word	0x20000008

0800083c <mini_pad>:
 800083c:	e92d 41f0 	stmdb	sp!, {r4, r5, r6, r7, r8, lr}
 8000840:	9f06      	ldr	r7, [sp, #24]
 8000842:	460d      	mov	r5, r1
 8000844:	4606      	mov	r6, r0
 8000846:	4611      	mov	r1, r2
 8000848:	b34b      	cbz	r3, 800089e <mini_pad+0x62>
 800084a:	42ab      	cmp	r3, r5
 800084c:	db2a      	blt.n	80008a4 <mini_pad+0x68>
 800084e:	f04f 0800 	mov.w	r8, #0
 8000852:	1b5c      	subs	r4, r3, r5
 8000854:	ea24 74e4 	bic.w	r4, r4, r4, asr #31
 8000858:	4622      	mov	r2, r4
 800085a:	4638      	mov	r0, r7
 800085c:	f7ff fc56 	bl	800010c <memset>
 8000860:	4630      	mov	r0, r6
 8000862:	193a      	adds	r2, r7, r4
 8000864:	1e53      	subs	r3, r2, #1
 8000866:	1974      	adds	r4, r6, r5
 8000868:	1a21      	subs	r1, r4, r0
 800086a:	2900      	cmp	r1, #0
 800086c:	dc1e      	bgt.n	80008ac <mini_pad+0x70>
 800086e:	2d00      	cmp	r5, #0
 8000870:	bfa8      	it	ge
 8000872:	1952      	addge	r2, r2, r5
 8000874:	1bd0      	subs	r0, r2, r7
 8000876:	f1b8 0f00 	cmp.w	r8, #0
 800087a:	d00e      	beq.n	800089a <mini_pad+0x5e>
 800087c:	42ba      	cmp	r2, r7
 800087e:	d90c      	bls.n	800089a <mini_pad+0x5e>
 8000880:	4611      	mov	r1, r2
 8000882:	232a      	movs	r3, #42	@ 0x2a
 8000884:	f801 3d01 	strb.w	r3, [r1, #-1]!
 8000888:	428f      	cmp	r7, r1
 800088a:	d206      	bcs.n	800089a <mini_pad+0x5e>
 800088c:	4611      	mov	r1, r2
 800088e:	f801 3d02 	strb.w	r3, [r1, #-2]!
 8000892:	428f      	cmp	r7, r1
 8000894:	bf38      	it	cc
 8000896:	f802 3c03 	strbcc.w	r3, [r2, #-3]
 800089a:	e8bd 81f0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, pc}
 800089e:	4698      	mov	r8, r3
 80008a0:	462b      	mov	r3, r5
 80008a2:	e7d6      	b.n	8000852 <mini_pad+0x16>
 80008a4:	461d      	mov	r5, r3
 80008a6:	f04f 0801 	mov.w	r8, #1
 80008aa:	e7d2      	b.n	8000852 <mini_pad+0x16>
 80008ac:	f810 1b01 	ldrb.w	r1, [r0], #1
 80008b0:	f803 1f01 	strb.w	r1, [r3, #1]!
 80008b4:	e7d8      	b.n	8000868 <mini_pad+0x2c>

080008b6 <_puts>:
 80008b6:	b5f0      	push	{r4, r5, r6, r7, lr}
 80008b8:	4604      	mov	r4, r0
 80008ba:	4608      	mov	r0, r1
 80008bc:	b142      	cbz	r2, 80008d0 <_puts+0x1a>
 80008be:	2100      	movs	r1, #0
 80008c0:	6817      	ldr	r7, [r2, #0]
 80008c2:	4281      	cmp	r1, r0
 80008c4:	6853      	ldr	r3, [r2, #4]
 80008c6:	db04      	blt.n	80008d2 <_puts+0x1c>
 80008c8:	2100      	movs	r1, #0
 80008ca:	7019      	strb	r1, [r3, #0]
 80008cc:	6850      	ldr	r0, [r2, #4]
 80008ce:	1bc0      	subs	r0, r0, r7
 80008d0:	bdf0      	pop	{r4, r5, r6, r7, pc}
 80008d2:	6895      	ldr	r5, [r2, #8]
 80008d4:	1e6e      	subs	r6, r5, #1
 80008d6:	6815      	ldr	r5, [r2, #0]
 80008d8:	4435      	add	r5, r6
 80008da:	42ab      	cmp	r3, r5
 80008dc:	d0f4      	beq.n	80008c8 <_puts+0x12>
 80008de:	1c5d      	adds	r5, r3, #1
 80008e0:	6055      	str	r5, [r2, #4]
 80008e2:	5c65      	ldrb	r5, [r4, r1]
 80008e4:	3101      	adds	r1, #1
 80008e6:	701d      	strb	r5, [r3, #0]
 80008e8:	e7eb      	b.n	80008c2 <_puts+0xc>

080008ea <mini_itoa.part.0>:
 80008ea:	b5f0      	push	{r4, r5, r6, r7, lr}
 80008ec:	2800      	cmp	r0, #0
 80008ee:	9c05      	ldr	r4, [sp, #20]
 80008f0:	da2c      	bge.n	800094c <mini_itoa.part.0+0x62>
 80008f2:	bb5b      	cbnz	r3, 800094c <mini_itoa.part.0+0x62>
 80008f4:	2601      	movs	r6, #1
 80008f6:	4240      	negs	r0, r0
 80008f8:	f012 0f01 	tst.w	r2, #1
 80008fc:	bf14      	ite	ne
 80008fe:	f04f 0c41 	movne.w	ip, #65	@ 0x41
 8000902:	f04f 0c61 	moveq.w	ip, #97	@ 0x61
 8000906:	4625      	mov	r5, r4
 8000908:	f1ac 0c0a 	sub.w	ip, ip, #10
 800090c:	4607      	mov	r7, r0
 800090e:	fbb0 f0f1 	udiv	r0, r0, r1
 8000912:	fb01 7310 	mls	r3, r1, r0, r7
 8000916:	b2da      	uxtb	r2, r3
 8000918:	2b09      	cmp	r3, #9
 800091a:	462b      	mov	r3, r5
 800091c:	bf94      	ite	ls
 800091e:	3230      	addls	r2, #48	@ 0x30
 8000920:	4462      	addhi	r2, ip
 8000922:	b2d2      	uxtb	r2, r2
 8000924:	428f      	cmp	r7, r1
 8000926:	f803 2b01 	strb.w	r2, [r3], #1
 800092a:	d211      	bcs.n	8000950 <mini_itoa.part.0+0x66>
 800092c:	b116      	cbz	r6, 8000934 <mini_itoa.part.0+0x4a>
 800092e:	222d      	movs	r2, #45	@ 0x2d
 8000930:	701a      	strb	r2, [r3, #0]
 8000932:	1cab      	adds	r3, r5, #2
 8000934:	2200      	movs	r2, #0
 8000936:	1b18      	subs	r0, r3, r4
 8000938:	701a      	strb	r2, [r3, #0]
 800093a:	eb00 72d0 	add.w	r2, r0, r0, lsr #31
 800093e:	1e61      	subs	r1, r4, #1
 8000940:	1052      	asrs	r2, r2, #1
 8000942:	4404      	add	r4, r0
 8000944:	1ae5      	subs	r5, r4, r3
 8000946:	4295      	cmp	r5, r2
 8000948:	db04      	blt.n	8000954 <mini_itoa.part.0+0x6a>
 800094a:	bdf0      	pop	{r4, r5, r6, r7, pc}
 800094c:	2600      	movs	r6, #0
 800094e:	e7d3      	b.n	80008f8 <mini_itoa.part.0+0xe>
 8000950:	461d      	mov	r5, r3
 8000952:	e7db      	b.n	800090c <mini_itoa.part.0+0x22>
 8000954:	f811 5f01 	ldrb.w	r5, [r1, #1]!
 8000958:	f813 6d01 	ldrb.w	r6, [r3, #-1]!
 800095c:	700e      	strb	r6, [r1, #0]
 800095e:	701d      	strb	r5, [r3, #0]
 8000960:	e7f0      	b.n	8000944 <mini_itoa.part.0+0x5a>
	...

08000964 <mini_vpprintf>:
 8000964:	e92d 4ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
 8000968:	4688      	mov	r8, r1
 800096a:	4614      	mov	r4, r2
 800096c:	461d      	mov	r5, r3
 800096e:	4606      	mov	r6, r0
 8000970:	b093      	sub	sp, #76	@ 0x4c
 8000972:	b908      	cbnz	r0, 8000978 <mini_vpprintf+0x14>
 8000974:	4680      	mov	r8, r0
 8000976:	4e58      	ldr	r6, [pc, #352]	@ (8000ad8 <mini_vpprintf+0x174>)
 8000978:	2300      	movs	r3, #0
 800097a:	9303      	str	r3, [sp, #12]
 800097c:	4627      	mov	r7, r4
 800097e:	f817 3b01 	ldrb.w	r3, [r7], #1
 8000982:	f88d 3017 	strb.w	r3, [sp, #23]
 8000986:	b91b      	cbnz	r3, 8000990 <mini_vpprintf+0x2c>
 8000988:	9803      	ldr	r0, [sp, #12]
 800098a:	b013      	add	sp, #76	@ 0x4c
 800098c:	e8bd 8ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
 8000990:	2b25      	cmp	r3, #37	@ 0x25
 8000992:	d00b      	beq.n	80009ac <mini_vpprintf+0x48>
 8000994:	4642      	mov	r2, r8
 8000996:	2101      	movs	r1, #1
 8000998:	f10d 0017 	add.w	r0, sp, #23
 800099c:	47b0      	blx	r6
 800099e:	46a9      	mov	r9, r5
 80009a0:	463c      	mov	r4, r7
 80009a2:	9b03      	ldr	r3, [sp, #12]
 80009a4:	464d      	mov	r5, r9
 80009a6:	4403      	add	r3, r0
 80009a8:	9303      	str	r3, [sp, #12]
 80009aa:	e7e7      	b.n	800097c <mini_vpprintf+0x18>
 80009ac:	2200      	movs	r2, #0
 80009ae:	7863      	ldrb	r3, [r4, #1]
 80009b0:	4617      	mov	r7, r2
 80009b2:	2b30      	cmp	r3, #48	@ 0x30
 80009b4:	bf0c      	ite	eq
 80009b6:	f04f 0b30 	moveq.w	fp, #48	@ 0x30
 80009ba:	f04f 0b20 	movne.w	fp, #32
 80009be:	f88d 3017 	strb.w	r3, [sp, #23]
 80009c2:	3402      	adds	r4, #2
 80009c4:	f1a3 0130 	sub.w	r1, r3, #48	@ 0x30
 80009c8:	b2c8      	uxtb	r0, r1
 80009ca:	2809      	cmp	r0, #9
 80009cc:	d922      	bls.n	8000a14 <mini_vpprintf+0xb0>
 80009ce:	b10a      	cbz	r2, 80009d4 <mini_vpprintf+0x70>
 80009d0:	f88d 3017 	strb.w	r3, [sp, #23]
 80009d4:	2f18      	cmp	r7, #24
 80009d6:	46ba      	mov	sl, r7
 80009d8:	bfa8      	it	ge
 80009da:	f04f 0a18 	movge.w	sl, #24
 80009de:	2b6c      	cmp	r3, #108	@ 0x6c
 80009e0:	bf02      	ittt	eq
 80009e2:	f814 3b01 	ldrbeq.w	r3, [r4], #1
 80009e6:	2101      	moveq	r1, #1
 80009e8:	f88d 3017 	strbeq.w	r3, [sp, #23]
 80009ec:	f89d 3017 	ldrb.w	r3, [sp, #23]
 80009f0:	bf18      	it	ne
 80009f2:	2100      	movne	r1, #0
 80009f4:	2b64      	cmp	r3, #100	@ 0x64
 80009f6:	d02e      	beq.n	8000a56 <mini_vpprintf+0xf2>
 80009f8:	d813      	bhi.n	8000a22 <mini_vpprintf+0xbe>
 80009fa:	2b58      	cmp	r3, #88	@ 0x58
 80009fc:	d04d      	beq.n	8000a9a <mini_vpprintf+0x136>
 80009fe:	2b63      	cmp	r3, #99	@ 0x63
 8000a00:	d05d      	beq.n	8000abe <mini_vpprintf+0x15a>
 8000a02:	2b00      	cmp	r3, #0
 8000a04:	d0c0      	beq.n	8000988 <mini_vpprintf+0x24>
 8000a06:	4642      	mov	r2, r8
 8000a08:	2101      	movs	r1, #1
 8000a0a:	f10d 0017 	add.w	r0, sp, #23
 8000a0e:	47b0      	blx	r6
 8000a10:	46a9      	mov	r9, r5
 8000a12:	e7c6      	b.n	80009a2 <mini_vpprintf+0x3e>
 8000a14:	230a      	movs	r3, #10
 8000a16:	2201      	movs	r2, #1
 8000a18:	fb03 1707 	mla	r7, r3, r7, r1
 8000a1c:	f814 3b01 	ldrb.w	r3, [r4], #1
 8000a20:	e7d0      	b.n	80009c4 <mini_vpprintf+0x60>
 8000a22:	2b75      	cmp	r3, #117	@ 0x75
 8000a24:	d017      	beq.n	8000a56 <mini_vpprintf+0xf2>
 8000a26:	2b78      	cmp	r3, #120	@ 0x78
 8000a28:	d037      	beq.n	8000a9a <mini_vpprintf+0x136>
 8000a2a:	2b73      	cmp	r3, #115	@ 0x73
 8000a2c:	d1eb      	bne.n	8000a06 <mini_vpprintf+0xa2>
 8000a2e:	46a9      	mov	r9, r5
 8000a30:	f859 5b04 	ldr.w	r5, [r9], #4
 8000a34:	4628      	mov	r0, r5
 8000a36:	f7ff fbb9 	bl	80001ac <strlen>
 8000a3a:	2f00      	cmp	r7, #0
 8000a3c:	4601      	mov	r1, r0
 8000a3e:	dd21      	ble.n	8000a84 <mini_vpprintf+0x120>
 8000a40:	af06      	add	r7, sp, #24
 8000a42:	465a      	mov	r2, fp
 8000a44:	4653      	mov	r3, sl
 8000a46:	4628      	mov	r0, r5
 8000a48:	9700      	str	r7, [sp, #0]
 8000a4a:	f7ff fef7 	bl	800083c <mini_pad>
 8000a4e:	4642      	mov	r2, r8
 8000a50:	4601      	mov	r1, r0
 8000a52:	4638      	mov	r0, r7
 8000a54:	e018      	b.n	8000a88 <mini_vpprintf+0x124>
 8000a56:	af0c      	add	r7, sp, #48	@ 0x30
 8000a58:	f105 0904 	add.w	r9, r5, #4
 8000a5c:	9700      	str	r7, [sp, #0]
 8000a5e:	b1a9      	cbz	r1, 8000a8c <mini_vpprintf+0x128>
 8000a60:	f1a3 0275 	sub.w	r2, r3, #117	@ 0x75
 8000a64:	4253      	negs	r3, r2
 8000a66:	4153      	adcs	r3, r2
 8000a68:	2200      	movs	r2, #0
 8000a6a:	210a      	movs	r1, #10
 8000a6c:	6828      	ldr	r0, [r5, #0]
 8000a6e:	f7ff ff3c 	bl	80008ea <mini_itoa.part.0>
 8000a72:	4653      	mov	r3, sl
 8000a74:	465a      	mov	r2, fp
 8000a76:	4601      	mov	r1, r0
 8000a78:	ad06      	add	r5, sp, #24
 8000a7a:	9500      	str	r5, [sp, #0]
 8000a7c:	4638      	mov	r0, r7
 8000a7e:	f7ff fedd 	bl	800083c <mini_pad>
 8000a82:	4601      	mov	r1, r0
 8000a84:	4642      	mov	r2, r8
 8000a86:	4628      	mov	r0, r5
 8000a88:	47b0      	blx	r6
 8000a8a:	e78a      	b.n	80009a2 <mini_vpprintf+0x3e>
 8000a8c:	2b75      	cmp	r3, #117	@ 0x75
 8000a8e:	d101      	bne.n	8000a94 <mini_vpprintf+0x130>
 8000a90:	2301      	movs	r3, #1
 8000a92:	e7e9      	b.n	8000a68 <mini_vpprintf+0x104>
 8000a94:	460b      	mov	r3, r1
 8000a96:	460a      	mov	r2, r1
 8000a98:	e7e7      	b.n	8000a6a <mini_vpprintf+0x106>
 8000a9a:	3b58      	subs	r3, #88	@ 0x58
 8000a9c:	af0c      	add	r7, sp, #48	@ 0x30
 8000a9e:	425a      	negs	r2, r3
 8000aa0:	9700      	str	r7, [sp, #0]
 8000aa2:	415a      	adcs	r2, r3
 8000aa4:	2110      	movs	r1, #16
 8000aa6:	2301      	movs	r3, #1
 8000aa8:	6828      	ldr	r0, [r5, #0]
 8000aaa:	f7ff ff1e 	bl	80008ea <mini_itoa.part.0>
 8000aae:	f105 0904 	add.w	r9, r5, #4
 8000ab2:	ad06      	add	r5, sp, #24
 8000ab4:	4601      	mov	r1, r0
 8000ab6:	4653      	mov	r3, sl
 8000ab8:	465a      	mov	r2, fp
 8000aba:	9500      	str	r5, [sp, #0]
 8000abc:	e7de      	b.n	8000a7c <mini_vpprintf+0x118>
 8000abe:	46a9      	mov	r9, r5
 8000ac0:	f859 3b04 	ldr.w	r3, [r9], #4
 8000ac4:	ad06      	add	r5, sp, #24
 8000ac6:	f88d 3017 	strb.w	r3, [sp, #23]
 8000aca:	465a      	mov	r2, fp
 8000acc:	4653      	mov	r3, sl
 8000ace:	2101      	movs	r1, #1
 8000ad0:	9500      	str	r5, [sp, #0]
 8000ad2:	f10d 0017 	add.w	r0, sp, #23
 8000ad6:	e7d2      	b.n	8000a7e <mini_vpprintf+0x11a>
 8000ad8:	080008b7 	.word	0x080008b7

08000adc <mini_vsnprintf>:
 8000adc:	b51f      	push	{r0, r1, r2, r3, r4, lr}
 8000ade:	4604      	mov	r4, r0
 8000ae0:	e9cd 0001 	strd	r0, r0, [sp, #4]
 8000ae4:	9103      	str	r1, [sp, #12]
 8000ae6:	b151      	cbz	r1, 8000afe <mini_vsnprintf+0x22>
 8000ae8:	b958      	cbnz	r0, 8000b02 <mini_vsnprintf+0x26>
 8000aea:	4621      	mov	r1, r4
 8000aec:	4806      	ldr	r0, [pc, #24]	@ (8000b08 <mini_vsnprintf+0x2c>)
 8000aee:	f7ff ff39 	bl	8000964 <mini_vpprintf>
 8000af2:	b114      	cbz	r4, 8000afa <mini_vsnprintf+0x1e>
 8000af4:	e9dd 3001 	ldrd	r3, r0, [sp, #4]
 8000af8:	1ac0      	subs	r0, r0, r3
 8000afa:	b004      	add	sp, #16
 8000afc:	bd10      	pop	{r4, pc}
 8000afe:	460c      	mov	r4, r1
 8000b00:	e7f3      	b.n	8000aea <mini_vsnprintf+0xe>
 8000b02:	a901      	add	r1, sp, #4
 8000b04:	e7f2      	b.n	8000aec <mini_vsnprintf+0x10>
 8000b06:	bf00      	nop
 8000b08:	080008b7 	.word	0x080008b7

08000b0c <ring_buffer_is_full>:
 8000b0c:	6842      	ldr	r2, [r0, #4]
 8000b0e:	e9d0 1302 	ldrd	r1, r3, [r0, #8]
 8000b12:	1a5b      	subs	r3, r3, r1
 8000b14:	439a      	bics	r2, r3
 8000b16:	bf0c      	ite	eq
 8000b18:	2001      	moveq	r0, #1
 8000b1a:	2000      	movne	r0, #0
 8000b1c:	4770      	bx	lr

08000b1e <ring_buffer_num_items>:
 8000b1e:	e9d0 2302 	ldrd	r2, r3, [r0, #8]
 8000b22:	6840      	ldr	r0, [r0, #4]
 8000b24:	1a9b      	subs	r3, r3, r2
 8000b26:	4018      	ands	r0, r3
 8000b28:	4770      	bx	lr

08000b2a <ring_buffer_init>:
 8000b2a:	2300      	movs	r3, #0
 8000b2c:	3a01      	subs	r2, #1
 8000b2e:	e9c0 3302 	strd	r3, r3, [r0, #8]
 8000b32:	6001      	str	r1, [r0, #0]
 8000b34:	6042      	str	r2, [r0, #4]
 8000b36:	4770      	bx	lr

08000b38 <ring_buffer_queue>:
 8000b38:	b538      	push	{r3, r4, r5, lr}
 8000b3a:	4604      	mov	r4, r0
 8000b3c:	460d      	mov	r5, r1
 8000b3e:	f7ff ffe5 	bl	8000b0c <ring_buffer_is_full>
 8000b42:	b120      	cbz	r0, 8000b4e <ring_buffer_queue+0x16>
 8000b44:	68a3      	ldr	r3, [r4, #8]
 8000b46:	6862      	ldr	r2, [r4, #4]
 8000b48:	3301      	adds	r3, #1
 8000b4a:	4013      	ands	r3, r2
 8000b4c:	60a3      	str	r3, [r4, #8]
 8000b4e:	68e3      	ldr	r3, [r4, #12]
 8000b50:	6822      	ldr	r2, [r4, #0]
 8000b52:	54d5      	strb	r5, [r2, r3]
 8000b54:	68e3      	ldr	r3, [r4, #12]
 8000b56:	6862      	ldr	r2, [r4, #4]
 8000b58:	3301      	adds	r3, #1
 8000b5a:	4013      	ands	r3, r2
 8000b5c:	60e3      	str	r3, [r4, #12]
 8000b5e:	bd38      	pop	{r3, r4, r5, pc}

08000b60 <ring_buffer_dequeue>:
 8000b60:	e9d0 3202 	ldrd	r3, r2, [r0, #8]
 8000b64:	429a      	cmp	r2, r3
 8000b66:	d009      	beq.n	8000b7c <ring_buffer_dequeue+0x1c>
 8000b68:	6802      	ldr	r2, [r0, #0]
 8000b6a:	5cd3      	ldrb	r3, [r2, r3]
 8000b6c:	700b      	strb	r3, [r1, #0]
 8000b6e:	6883      	ldr	r3, [r0, #8]
 8000b70:	6842      	ldr	r2, [r0, #4]
 8000b72:	3301      	adds	r3, #1
 8000b74:	4013      	ands	r3, r2
 8000b76:	6083      	str	r3, [r0, #8]
 8000b78:	2001      	movs	r0, #1
 8000b7a:	4770      	bx	lr
 8000b7c:	2000      	movs	r0, #0
 8000b7e:	4770      	bx	lr

08000b80 <ring_buffer_dequeue_arr>:
 8000b80:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 8000b82:	4617      	mov	r7, r2
 8000b84:	e9d0 3202 	ldrd	r3, r2, [r0, #8]
 8000b88:	429a      	cmp	r2, r3
 8000b8a:	4605      	mov	r5, r0
 8000b8c:	460e      	mov	r6, r1
 8000b8e:	f04f 0400 	mov.w	r4, #0
 8000b92:	d007      	beq.n	8000ba4 <ring_buffer_dequeue_arr+0x24>
 8000b94:	42bc      	cmp	r4, r7
 8000b96:	eb06 0104 	add.w	r1, r6, r4
 8000b9a:	d003      	beq.n	8000ba4 <ring_buffer_dequeue_arr+0x24>
 8000b9c:	4628      	mov	r0, r5
 8000b9e:	f7ff ffdf 	bl	8000b60 <ring_buffer_dequeue>
 8000ba2:	b908      	cbnz	r0, 8000ba8 <ring_buffer_dequeue_arr+0x28>
 8000ba4:	4620      	mov	r0, r4
 8000ba6:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
 8000ba8:	3401      	adds	r4, #1
 8000baa:	e7f3      	b.n	8000b94 <ring_buffer_dequeue_arr+0x14>

08000bac <ring_buffer_peek>:
 8000bac:	b538      	push	{r3, r4, r5, lr}
 8000bae:	4614      	mov	r4, r2
 8000bb0:	4605      	mov	r5, r0
 8000bb2:	f7ff ffb4 	bl	8000b1e <ring_buffer_num_items>
 8000bb6:	42a0      	cmp	r0, r4
 8000bb8:	d908      	bls.n	8000bcc <ring_buffer_peek+0x20>
 8000bba:	2001      	movs	r0, #1
 8000bbc:	68ab      	ldr	r3, [r5, #8]
 8000bbe:	441c      	add	r4, r3
 8000bc0:	686b      	ldr	r3, [r5, #4]
 8000bc2:	401c      	ands	r4, r3
 8000bc4:	682b      	ldr	r3, [r5, #0]
 8000bc6:	5d1b      	ldrb	r3, [r3, r4]
 8000bc8:	700b      	strb	r3, [r1, #0]
 8000bca:	bd38      	pop	{r3, r4, r5, pc}
 8000bcc:	2000      	movs	r0, #0
 8000bce:	e7fc      	b.n	8000bca <ring_buffer_peek+0x1e>

08000bd0 <hardware_init>:
 8000bd0:	b508      	push	{r3, lr}
 8000bd2:	f7ff fd31 	bl	8000638 <delay_init>
 8000bd6:	f7ff fd67 	bl	80006a8 <led_init>
 8000bda:	f44f 60a0 	mov.w	r0, #1280	@ 0x500
 8000bde:	f7ff fbaf 	bl	8000340 <NVIC_PriorityGroupConfig>
 8000be2:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
 8000be6:	f44f 30e1 	mov.w	r0, #115200	@ 0x1c200
 8000bea:	f7ff bdc7 	b.w	800077c <uart_init>
	...

08000bf0 <main>:
 8000bf0:	b5f0      	push	{r4, r5, r6, r7, lr}
 8000bf2:	2400      	movs	r4, #0
 8000bf4:	b091      	sub	sp, #68	@ 0x44
 8000bf6:	2240      	movs	r2, #64	@ 0x40
 8000bf8:	2100      	movs	r1, #0
 8000bfa:	4668      	mov	r0, sp
 8000bfc:	f7ff fa86 	bl	800010c <memset>
 8000c00:	f7ff ffe6 	bl	8000bd0 <hardware_init>
 8000c04:	4810      	ldr	r0, [pc, #64]	@ (8000c48 <main+0x58>)
 8000c06:	f7ff fda5 	bl	8000754 <usart_printf>
 8000c0a:	4625      	mov	r5, r4
 8000c0c:	2664      	movs	r6, #100	@ 0x64
 8000c0e:	4f0f      	ldr	r7, [pc, #60]	@ (8000c4c <main+0x5c>)
 8000c10:	4668      	mov	r0, sp
 8000c12:	f7ff fd7d 	bl	8000710 <usart_gets>
 8000c16:	f010 02ff 	ands.w	r2, r0, #255	@ 0xff
 8000c1a:	d004      	beq.n	8000c26 <main+0x36>
 8000c1c:	4669      	mov	r1, sp
 8000c1e:	4638      	mov	r0, r7
 8000c20:	f7ff fd98 	bl	8000754 <usart_printf>
 8000c24:	e7f4      	b.n	8000c10 <main+0x20>
 8000c26:	3401      	adds	r4, #1
 8000c28:	b2a4      	uxth	r4, r4
 8000c2a:	fbb4 f3f6 	udiv	r3, r4, r6
 8000c2e:	fb06 4313 	mls	r3, r6, r3, r4
 8000c32:	b29b      	uxth	r3, r3
 8000c34:	b923      	cbnz	r3, 8000c40 <main+0x50>
 8000c36:	f085 0501 	eor.w	r5, r5, #1
 8000c3a:	4628      	mov	r0, r5
 8000c3c:	f7ff fd4c 	bl	80006d8 <led_switch>
 8000c40:	200a      	movs	r0, #10
 8000c42:	f7ff fd17 	bl	8000674 <delay_ms>
 8000c46:	e7e3      	b.n	8000c10 <main+0x20>
 8000c48:	08000c64 	.word	0x08000c64
 8000c4c:	08000c7b 	.word	0x08000c7b

08000c50 <ADCPrescTable>:
 8000c50:	08060402                                ....

08000c54 <APBAHBPrescTable>:
 8000c54:	00000000 04030201 04030201 09080706     ................
 8000c64:	6c6c6568 796d206f 6e696d20 72702069     hello my mini pr
 8000c74:	66746e69 67000a0d 64207465 20617461     intf...get data 
 8000c84:	203a7369 6c287325 253d6e65 000a2964     is: %s(len=%d)..
