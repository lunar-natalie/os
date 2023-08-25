/*
 * isr.s
 *
 * Copyright (c) 2023 Natalie Wiggins <islifepeachy@outlook.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/*
 * Creates an ISR wrapper (isr_handler_irqN) for a given IRQ 'irq', which calls
 * an externally defined handler with the symbol 'handler'.
 */
.macro isr_handler_extern irq handler
.extern \handler
.global isr_handler_irq\irq
.type isr_handler_irq\irq, @function
.align 4		/* SysV ABI requires 32-bit alignment */
isr_handler_irq\irq:
	pusha
	cld		/* SysV ABI requires DF to be clear on function entry */
	call	\handler
	popa
	iret
.endm

/*
 * Creates an empty ISR wrapper (isr_handler_irqN) for a given IRQ 'irq'.
 */
.macro isr_handler_empty irq
.global isr_handler_irq\irq
.type isr_handler_irq\irq, @function
.align 4		/* SysV ABI requires 32-bit alignment */
isr_handler_irq\irq:
	pusha
	cld		/* SysV ABI requires DF to be clear on function entry */
	popa
	iret
.endm

.section .text

/* ISRs for IRQs 0-255. */
isr_handler_empty 0
isr_handler_empty 1
isr_handler_empty 2
isr_handler_empty 3
isr_handler_empty 4
isr_handler_empty 5
isr_handler_empty 6
isr_handler_empty 7
isr_handler_empty 8
isr_handler_empty 9
isr_handler_empty 10
isr_handler_empty 11
isr_handler_empty 12
isr_handler_empty 13
isr_handler_empty 14
isr_handler_empty 15
isr_handler_empty 16
isr_handler_empty 17
isr_handler_empty 18
isr_handler_empty 19
isr_handler_empty 20
isr_handler_empty 21
isr_handler_empty 22
isr_handler_empty 23
isr_handler_empty 24
isr_handler_empty 25
isr_handler_empty 26
isr_handler_empty 27
isr_handler_empty 28
isr_handler_empty 29
isr_handler_empty 30
isr_handler_empty 31
isr_handler_empty 32
isr_handler_empty 33
isr_handler_empty 34
isr_handler_empty 35
isr_handler_empty 36
isr_handler_empty 37
isr_handler_empty 38
isr_handler_empty 39
isr_handler_empty 40
isr_handler_empty 41
isr_handler_empty 42
isr_handler_empty 43
isr_handler_empty 44
isr_handler_empty 45
isr_handler_empty 46
isr_handler_empty 47
isr_handler_empty 48
isr_handler_empty 49
isr_handler_empty 50
isr_handler_empty 51
isr_handler_empty 52
isr_handler_empty 53
isr_handler_empty 54
isr_handler_empty 55
isr_handler_empty 56
isr_handler_empty 57
isr_handler_empty 58
isr_handler_empty 59
isr_handler_empty 60
isr_handler_empty 61
isr_handler_empty 62
isr_handler_empty 63
isr_handler_empty 64
isr_handler_empty 65
isr_handler_empty 66
isr_handler_empty 67
isr_handler_empty 68
isr_handler_empty 69
isr_handler_empty 70
isr_handler_empty 71
isr_handler_empty 72
isr_handler_empty 73
isr_handler_empty 74
isr_handler_empty 75
isr_handler_empty 76
isr_handler_empty 77
isr_handler_empty 78
isr_handler_empty 79
isr_handler_empty 80
isr_handler_empty 81
isr_handler_empty 82
isr_handler_empty 83
isr_handler_empty 84
isr_handler_empty 85
isr_handler_empty 86
isr_handler_empty 87
isr_handler_empty 88
isr_handler_empty 89
isr_handler_empty 90
isr_handler_empty 91
isr_handler_empty 92
isr_handler_empty 93
isr_handler_empty 94
isr_handler_empty 95
isr_handler_empty 96
isr_handler_empty 97
isr_handler_empty 98
isr_handler_empty 99
isr_handler_empty 100
isr_handler_empty 101
isr_handler_empty 102
isr_handler_empty 103
isr_handler_empty 104
isr_handler_empty 105
isr_handler_empty 106
isr_handler_empty 107
isr_handler_empty 108
isr_handler_empty 109
isr_handler_empty 110
isr_handler_empty 111
isr_handler_empty 112
isr_handler_empty 113
isr_handler_empty 114
isr_handler_empty 115
isr_handler_empty 116
isr_handler_empty 117
isr_handler_empty 118
isr_handler_empty 119
isr_handler_empty 120
isr_handler_empty 121
isr_handler_empty 122
isr_handler_empty 123
isr_handler_empty 124
isr_handler_empty 125
isr_handler_empty 126
isr_handler_empty 127
isr_handler_empty 128
isr_handler_empty 129
isr_handler_empty 130
isr_handler_empty 131
isr_handler_empty 132
isr_handler_empty 133
isr_handler_empty 134
isr_handler_empty 135
isr_handler_empty 136
isr_handler_empty 137
isr_handler_empty 138
isr_handler_empty 139
isr_handler_empty 140
isr_handler_empty 141
isr_handler_empty 142
isr_handler_empty 143
isr_handler_empty 144
isr_handler_empty 145
isr_handler_empty 146
isr_handler_empty 147
isr_handler_empty 148
isr_handler_empty 149
isr_handler_empty 150
isr_handler_empty 151
isr_handler_empty 152
isr_handler_empty 153
isr_handler_empty 154
isr_handler_empty 155
isr_handler_empty 156
isr_handler_empty 157
isr_handler_empty 158
isr_handler_empty 159
isr_handler_empty 160
isr_handler_empty 161
isr_handler_empty 162
isr_handler_empty 163
isr_handler_empty 164
isr_handler_empty 165
isr_handler_empty 166
isr_handler_empty 167
isr_handler_empty 168
isr_handler_empty 169
isr_handler_empty 170
isr_handler_empty 171
isr_handler_empty 172
isr_handler_empty 173
isr_handler_empty 174
isr_handler_empty 175
isr_handler_empty 176
isr_handler_empty 177
isr_handler_empty 178
isr_handler_empty 179
isr_handler_empty 180
isr_handler_empty 181
isr_handler_empty 182
isr_handler_empty 183
isr_handler_empty 184
isr_handler_empty 185
isr_handler_empty 186
isr_handler_empty 187
isr_handler_empty 188
isr_handler_empty 189
isr_handler_empty 190
isr_handler_empty 191
isr_handler_empty 192
isr_handler_empty 193
isr_handler_empty 194
isr_handler_empty 195
isr_handler_empty 196
isr_handler_empty 197
isr_handler_empty 198
isr_handler_empty 199
isr_handler_empty 200
isr_handler_empty 201
isr_handler_empty 202
isr_handler_empty 203
isr_handler_empty 204
isr_handler_empty 205
isr_handler_empty 206
isr_handler_empty 207
isr_handler_empty 208
isr_handler_empty 209
isr_handler_empty 210
isr_handler_empty 211
isr_handler_empty 212
isr_handler_empty 213
isr_handler_empty 214
isr_handler_empty 215
isr_handler_empty 216
isr_handler_empty 217
isr_handler_empty 218
isr_handler_empty 219
isr_handler_empty 220
isr_handler_empty 221
isr_handler_empty 222
isr_handler_empty 223
isr_handler_empty 224
isr_handler_empty 225
isr_handler_empty 226
isr_handler_empty 227
isr_handler_empty 228
isr_handler_empty 229
isr_handler_empty 230
isr_handler_empty 231
isr_handler_empty 232
isr_handler_empty 233
isr_handler_empty 234
isr_handler_empty 235
isr_handler_empty 236
isr_handler_empty 237
isr_handler_empty 238
isr_handler_empty 239
isr_handler_empty 240
isr_handler_empty 241
isr_handler_empty 242
isr_handler_empty 243
isr_handler_empty 244
isr_handler_empty 245
isr_handler_empty 246
isr_handler_empty 247
isr_handler_empty 248
isr_handler_empty 249
isr_handler_empty 250
isr_handler_empty 251
isr_handler_empty 252
isr_handler_empty 253
isr_handler_empty 254
isr_handler_empty 255
