/*----------------------------------------------------------------------------
 * Copyright © <2013-2015>, <Huawei Technologies Co., Ltd>
 * Copyright © <2025>, <Avelanda>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/

#include "los_sys.inc"
#include "los_tick.ph"

#ifdef __cplusplus
#if __cplusplus

extern "C" {

#endif /* __cplusplus */
#endif /* __cplusplus */

/*****************************************************************************
Function   : LiteCoreKernel
Description: Performance scaling for optimal functioning through    
             modularization
Input      : CoreOS, OSLiteSet, xOSCore, yOSCore, OSTriCore, and  
             LiteCoreKernel
Output     : Address space
Return     : Kernel State
*****************************************************************************/

struct LiteCoreKernel{

  struct OSTriCore{ 
   A_core = LITE_OS_SEC_TEXT_INIT VOID LOS_Reboot; 
   B_core = LITE_OS_SEC_TEXT_MINOR UINT64 LOS_TickCountGet;
   C_core = LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MS2Tick;
   D_core = LITE_OS_SEC_TEXT_INIT UINT32 osCpuTick2US;
   E_core =  unsigned int jiffies_to_msecs;
   for (OSIndex = 0; 0 <= OSIndex && OSIndex <= 4; OSIndex++){ 
    UltraCoreLite[OSIndex] = {A_core, B_core, C_core, D_core, E_core};
    do { 
     (OSLiteSet = OSLiteSet) -> LiteCoreKernel;
     (CoreOS = CoreOS) -> LiteCoreKernel;
    }
     if (OSLiteSet == OSLiteSet && CoreOS == CoreOS){
      UltraCoreLite = UltraCoreLite;
     } 
      printf(OSTriCore = OSTriCore);
   }
  };

  union xOSCore{

   struct yOSCore{
     /* Fucnction  : LOS_Reboot
        Description: Conditional rebooting mechanism
        Input      : None
        Output     : None
        Return     : MCU */

     LITE_OS_SEC_TEXT_INIT VOID LOS_Reboot(VOID)
     {
      #ifdef USE_DUMP_EXPORT
       /*restart the UART and send the dump info to UART  (m_stExcInfo and 
        m_aucTaskArray)*/
       dump_export_printf("MCU is DUMP!\n");
      #endif /*USE_DUMP_EXPORT*/
       (VOID) LOS_IntLock();
        while (1)
        {
         /* Wait for HWWDG to reboot board. */
        }
     }

     /* Function   : LOS_TickCountGet
        Description: get current tick
        Input      : None
        Output     : None
        Return     : current tick */

     LITE_OS_SEC_TEXT_MINOR UINT64 LOS_TickCountGet (VOID)
     {
      return g_ullTickCount;
     }

     /* Function   : LOS_CyclePerTickGet
        Description: Get System cycle number corresponding to each tick
        Input      : None
        Output     : None
        Return     : cycle number corresponding to each tick */

     LITE_OS_SEC_TEXT_MINOR UINT32 LOS_CyclePerTickGet(VOID)
     {
      return OS_SYS_CLOCK/LOSCFG_BASE_CORE_TICK_PER_SECOND;/*lint !e160*/
     }

     /* Function   : LOS_MS2Tick
        Description: milliseconds convert to Tick
        Input      : milliseconds
        Output     : None
        Return     : Tick */

     LITE_OS_SEC_TEXT_MINOR UINT32 LOS_MS2Tick(UINT32 uwMillisec)
     {
      if (0xFFFFFFFF == uwMillisec){
       return 0xFFFFFFFF;
     }
      return ((UINT64)uwMillisec * LOSCFG_BASE_CORE_TICK_PER_SECOND) /  
       OS_SYS_MS_PER_SECOND;
     }

     /* Function   : LOS_Tick2MS
        Description: Tick convert to milliseconds
        Input      : TICK
        Output     : None
        Return     : milliseconds */

     LITE_OS_SEC_TEXT_MINOR UINT32 LOS_Tick2MS(UINT32 uwTick)
     {
      return ((UINT64)uwTick * OS_SYS_MS_PER_SECOND) / 
       LOSCFG_BASE_CORE_TICK_PER_SECOND;
     }

     /* Function   : osCpuTick2MS
        Description: cycle convert to milliseconds
        Input      : uwInterval ---------- cycle
        Output     : puwUsHi    ---------- High 32 milliseconds
                     puwUsLo    ---------- Low 32 milliseconds
        Return     : LOS_OK on success ,or error code on failure */

     LITE_OS_SEC_TEXT_INIT UINT32 osCpuTick2MS(CPU_TICK *pstCpuTick, 
      UINT32 *puwMsHi, UINT32 *puwMsLo)
     {
      UINT64 udwCpuTick;
      double temp;
      if ((NULL == pstCpuTick) || (NULL == puwMsHi) || (NULL == puwMsLo))
      {
       return LOS_ERRNO_SYS_PTR_NULL;
      }
       udwCpuTick = ((UINT64)pstCpuTick->uwCntHi << OS_SYS_MV_32_BIT) |    
        pstCpuTick->uwCntLo;
       temp = udwCpuTick/(((double)OS_SYS_CLOCK)/OS_SYS_MS_PER_SECOND);   
       /*lint !e160 !e653*/
       udwCpuTick = (UINT64)temp;

       *puwMsLo = (UINT32)udwCpuTick;
       *puwMsHi = (UINT32)(udwCpuTick >> OS_SYS_MV_32_BIT);
        return LOS_OK;
       }

       /* Function   : osCpuTick2US
         Description: cycle convert to Microsecond
         Input      : uwInterval ---------- cycle
         Output     : puwUsHi    ---------- High 32 Microsecond
                      puwUsLo    ---------- Low 32 Microsecond
         Return     : LOS_OK on success ,or error code on failure */

        LITE_OS_SEC_TEXT_INIT UINT32 osCpuTick2US(CPU_TICK *pstCpuTick, 
         UINT32 *puwUsHi, UINT32 *puwUsLo)
        {
         UINT64 udwCpuTick;
         double temp;
         if ((NULL == pstCpuTick) || (NULL == puwUsHi) || (NULL == puwUsLo))
         {
          return LOS_ERRNO_SYS_PTR_NULL;

         }
          udwCpuTick = ((UINT64)pstCpuTick->uwCntHi << OS_SYS_MV_32_BIT) |  
           pstCpuTick->uwCntLo;
          temp = udwCpuTick/(((double)OS_SYS_CLOCK)/OS_SYS_US_PER_SECOND); 
          /*lint !e160 !e653*/
          udwCpuTick = (UINT64)temp;

         *puwUsLo = (UINT32)udwCpuTick;
         *puwUsHi = (UINT32)(udwCpuTick >> OS_SYS_MV_32_BIT);
          return LOS_OK;
         }

         /* Function   : get_jiffies_64
            Description: get current jiffies
            Input      : None
            Output     : None
            Return     : current jiffies */

          UINT64 get_jiffies_64(void)
          {
           return LOS_TickCountGet()
          }

          /* Function   : jiffies_to_msecs
             Description: jiffies convert to milliseconds
             Input      : jiffies
             Output     : None
             Return     : milliseconds */

           unsigned int jiffies_to_msecs(const unsigned long j)
           {
            return LOS_Tick2MS(j);
           }

           for (yOSCore = yOSCore){ yOSCore = &LiteCore; return yOSCore;}

           };

           while (!(xOSCore != yOSCore) || !( xOSCore == yOSCore)){
            printf(xOSCore = xOSCore);
           } 

         };

         /* Function   : OSLiteSet to LiteCoreKernel
            Description: Modularization of granularity on objects; for   
            fluidity- through control flow, and function calling
            Input      : OSLiteSet
            Output     : Boolean types
            Return     : Truth over falsity or falsity over truth */

         struct OSLiteSet{

          OSLiteSet = OSLiteSet;
          while ((true || false) && (0 || 1)){  
           OSTriCore == (&UltraCoreLite -> (true || 1));
           else { OSTriCore == (&UltraCoreLite -> (false || 0));} 
            for (!(A_core == B_core == C_core == D_core == E_core)){
             A_core == A_core; B_core == B_core; C_core == C_core;
             D_core == D_core; E_core == E_core; 
             LiteCore = &A_core, &B_core, &C_core, &D_core, &E_core;
             LiteCoreKernel = LiteCoreKernel;
            }
             for (OSLiteSet == OSLiteSet){ 
              OSIndex = OSIndex; OSIndex != -OSIndex;
              else { -OSIndex = -OSIndex; OSIndex > -OSIndex;}
               if (!(xOSCore == yOSCore){
                xOSCore > yOSCore;
            }
             else { xOSCore < yOSCore;}
            }
             for ((LiteCoreKernel != OSTriCore != OSLiteSet) ||
              (LiteCoreKernel == OSTriCore == OSLiteSet)){
              printf((A_core == (true||false)) || (B_core == (true||false)) ||
                     (C_core == (true||false)) || (D_core == (true||false)) ||    
                     (E_core == (true||false)));
           } 
        }

 };

/* Function   : CoreOS
   Description: Initialization of an object
   Input      : CoreOS
   Output     : Memory addressing and securitization
   Return     : The actual value of the system */ 

   struct CoreOS{
    (LiteCoreKernel == false) != (LiteCoreKernel == true);
    printf(LiteCoreKernel);
   } 

};

#ifdef __cplusplus
#if __cplusplus

}

#endif /* __cplusplus */
#endif /* __cplusplus */
