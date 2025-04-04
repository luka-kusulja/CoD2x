
/*
__asm__ (
    "assembly_code"            // The actual assembly code
    : output_operands           // Output constraints
    : input_operands            // Input constraints
    : clobbers                  // Clobbered registers or flags
);

Common constraint types:
    r: Use a general-purpose register.
    m: Use memory (the variable's address in memory).
    i: Use an immediate value.
    =r: Writable register for output.
    +r: A register that's both an input and an output.

Clobbers specify which registers, memory, or flags are modified by the assembly code but are not part of the inputs or outputs. 
The compiler uses this information to avoid using those resources for other purposes.

If the assembly code modifies global memory (e.g., via pointers), add "memory" to the clobber list to tell the compiler that memory content has changed:

*/


/*
    Helper macros for inline assembly
*/

#define ASM(op, ...) ASM__##op(__VA_ARGS__)

#define ASM__push(arg) \
    __asm__ volatile("push %0\n" : : "m"(arg) : "memory")

#define ASM__mov(dest, src) \
    __asm__ volatile("movl %0, %%" dest "\n" : : "m"(src) : "memory", dest)

#define ASM__call(func) \
    __asm__ volatile("call *%0\n" : : "m"(func) : "memory")

#define ASM__add(dest, imm) \
    __asm__ volatile("addl %0, %%" dest "\n" : : "i"(imm) : "memory", dest)

#define ASM__add_esp(bytes) \
    __asm__ volatile("addl %0, %%esp\n" : : "i"(bytes) : "memory")

#define ASM__movr(dest, src) \
    __asm__ volatile("movl %%" src ", %0\n" : "=m"(dest) : : "memory", src)


/*
Macros to make inline function call easy.
Example:
ASM_CALL(RETURN_VOID, 0x00434460, 1, EAX(var1), ECX(var2), PUSH(var3));
*/
#define EAX(var) ASM__mov("eax", var)
#define EBX(var) ASM__mov("ebx", var)
#define ECX(var) ASM__mov("ecx", var)
#define EDX(var) ASM__mov("edx", var)
#define EDI(var) ASM__mov("edi", var)
#define ESI(var) ASM__mov("esi", var)
#define PUSH(var) ASM__push(var)
#define RETURN(var) ASM__movr(var, "eax")
#define RETURN_VOID

// Push 32-bit word from a struct by offset.
#define ASM_PUSH_OFFSET(ptr, offset)                         \
    ASM__push(*((unsigned int *)((char*)(ptr) + (offset))));

// Macros for pushing in reverse order (highest offset first).
#define ASM_PUSH_STRUCT_OF_SIZE_1(ptr)   \
    ASM_PUSH_OFFSET(ptr, 0)
#define ASM_PUSH_STRUCT_OF_SIZE_2(ptr)   \
    ASM_PUSH_OFFSET(ptr, 4)              \
    ASM_PUSH_STRUCT_OF_SIZE_1(ptr)
#define ASM_PUSH_STRUCT_OF_SIZE_3(ptr)   \
    ASM_PUSH_OFFSET(ptr, 8)              \
    ASM_PUSH_STRUCT_OF_SIZE_2(ptr)
#define ASM_PUSH_STRUCT_OF_SIZE_4(ptr)   \
    ASM_PUSH_OFFSET(ptr, 12)             \
    ASM_PUSH_STRUCT_OF_SIZE_3(ptr)
#define ASM_PUSH_STRUCT_OF_SIZE_5(ptr)   \
    ASM_PUSH_OFFSET(ptr, 16)             \
    ASM_PUSH_STRUCT_OF_SIZE_4(ptr)

#define ASM_PUSH_STRUCT_OF_SIZE(ptr, cnt)  ASM_PUSH_STRUCT_OF_SIZE_##cnt(ptr)

/**
 * Push specified number of 32bit fields of struct on the stack.
 * @param ptr Pointer to struct to push on the stack
 * @param cnt Number of 32-bit words to copy
 */
#define PUSH_STRUCT(ptr, cnt)  ASM_PUSH_STRUCT_OF_SIZE(&(ptr), cnt)


#define ASM_CALL_10(ret, func, stack, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10 )  \
    const void* original_func = (void*)func; \
    a10; \
    a9; \
    a8; \
    a7; \
    a6; \
    a5; \
    a4; \
    a3; \
    a2; \
    a1; \
    ASM__call(original_func); \
    ret; \
    ASM__add_esp(stack * 4);

#define ASM_CALL_9(ret, func, stack, a1, a2, a3, a4, a5, a6, a7, a8, a9 )   ASM_CALL_10(ret, func, stack, a1, a2, a3, a4, a5, a6, a7, a8, a9, RETURN_VOID)
#define ASM_CALL_8(ret, func, stack, a1, a2, a3, a4, a5, a6, a7, a8 )       ASM_CALL_9 (ret, func, stack, a1, a2, a3, a4, a5, a6, a7, a8, RETURN_VOID)
#define ASM_CALL_7(ret, func, stack, a1, a2, a3, a4, a5, a6, a7 )           ASM_CALL_8 (ret, func, stack, a1, a2, a3, a4, a5, a6, a7, RETURN_VOID)
#define ASM_CALL_6(ret, func, stack, a1, a2, a3, a4, a5, a6 )               ASM_CALL_7 (ret, func, stack, a1, a2, a3, a4, a5, a6, RETURN_VOID)
#define ASM_CALL_5(ret, func, stack, a1, a2, a3, a4, a5 )                   ASM_CALL_6 (ret, func, stack, a1, a2, a3, a4, a5, RETURN_VOID)
#define ASM_CALL_4(ret, func, stack, a1, a2, a3, a4 )                       ASM_CALL_5 (ret, func, stack, a1, a2, a3, a4, RETURN_VOID)
#define ASM_CALL_3(ret, func, stack, a1, a2, a3 )                           ASM_CALL_4 (ret, func, stack, a1, a2, a3, RETURN_VOID)
#define ASM_CALL_2(ret, func, stack, a1, a2 )                               ASM_CALL_3 (ret, func, stack, a1, a2, RETURN_VOID)
#define ASM_CALL_1(ret, func, stack, a1 )                                   ASM_CALL_2 (ret, func, stack, a1, RETURN_VOID)

#define GET_ASM_CALL_MACRO(ret, func, stack, _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME

/**
 * Call a function with a variable number of arguments.
 * 
 * Example:
 * `ASM_CALL(RETURN_VOID, 0x00434460, 3, PUSH(var1), PUSH(var2), PUSH(var3));`
 * 
 * @param ret 1. Return value - can be RETURN_VOID or RETURN(variable)
 * @param func 2. Function address
 * @param stack 3. Number of arguments pushed on the stack
 * @param ... 4. Arguments of the function - can be PUSH(variable) or EAX(variable), ECX(variable), etc.
 */
#define ASM_CALL(...) \
    GET_ASM_CALL_MACRO(__VA_ARGS__, \
        ASM_CALL_10, ASM_CALL_9, ASM_CALL_8, ASM_CALL_7, ASM_CALL_6, ASM_CALL_5, ASM_CALL_4, ASM_CALL_3, ASM_CALL_2, ASM_CALL_1)(__VA_ARGS__)
