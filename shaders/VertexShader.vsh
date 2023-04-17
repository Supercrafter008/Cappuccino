; $MODE = "UniformRegister"

; $SPI_VS_OUT_CONFIG.VS_EXPORT_COUNT = 0
; $NUM_SPI_VS_OUT_ID = 1

; texCoords
; $SPI_VS_OUT_ID[0].SEMANTIC_0 = 0

; C0
; $UNIFORM_VARS[0].name = "uOffset"
; $UNIFORM_VARS[0].type = "vec3"
; $UNIFORM_VARS[0].count = 1
; $UNIFORM_VARS[0].block = -1
; $UNIFORM_VARS[0].offset = 0

; C1
; $UNIFORM_VARS[1].name = "uScale"
; $UNIFORM_VARS[1].type = "vec2"
; $UNIFORM_VARS[1].count = 1
; $UNIFORM_VARS[1].block = -1
; $UNIFORM_VARS[1].offset = 4

; R1
; $ATTRIB_VARS[0].name = "aPosition"
; $ATTRIB_VARS[0].type = "vec2"
; $ATTRIB_VARS[0].location = 0

; R2
; $ATTRIB_VARS[1].name = "aTexPos"
; $ATTRIB_VARS[1].type = "vec2"
; $ATTRIB_VARS[1].location = 1

0 CALL_FS NO_BARRIER 
01 ALU: ADDR(32) CNT(5) 
      0  x: MULADD      R1.x,  R1.x,  C1.x,  C0.x   
         y: MULADD      R1.y,  R1.y,  C1.y,  C0.y
         t: MOV         R1.z,  C0.z   
         w: MOV         R1.w,  1.0f     
02 EXP_DONE: POS0, R1
03 EXP_DONE: PARAM0, R2.xyzz NO_BARRIER
END_OF_PROGRAM