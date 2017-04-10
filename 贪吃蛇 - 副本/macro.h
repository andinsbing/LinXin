#pragma once 

// for tracing MACRO
void macroTracingLog(bool on,const char* info);

#define MACRO_ON

#ifdef MACRO_ON
#define ASSERT_TRUE(x,info) { macroTracingLog(!(x),info); }
#else
#define ASSERT_TRUE(x,info)
#endif

#define ASSERT_LOG(info) {ASSERT_TRUE(false,info) }
#define ASSERT_FALSE(x,info)  { ASSERT_TRUE(!(x),info)  } 
#define ASSERT_NOT_NULLPTR(x,info) {ASSERT_TRUE(x,info) }

#define ASSERT_OP_TURE(x,op,y,info)  { ASSERT_TRUE( (x) op (y) ,info) }

#define ASSERT_EQUAL(x,y,info)  { ASSERT_OP_TURE(x,==,y,info) }
#define ASSERT_NOT_EQUAL(x,y,info) {  ASSERT_OP_TURE(x,!=,y,info) }
#define ASSERT_LESS_THAN(x,limit,info)  { ASSERT_OP_TURE(x,<,limit,info) }
#define ASSERT_LESSEQU_THAN(x,limit,info) { ASSERT_OP_TURE(x,<=,limit,info) }
#define ASSERT_GREAT_THAN(x,limit,info)  { ASSERT_OP_TURE(x,>,limit,info) }
#define ASSERT_GREATEQU_THAN(x,limit,info)  { ASSERT_OP_TURE(x,>=,limit,info) }
