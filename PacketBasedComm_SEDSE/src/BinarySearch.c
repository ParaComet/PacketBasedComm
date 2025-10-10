#include "BinarySearch.h"

BNRSCH_U1 BNRSCH_find0(
    const void* datas,
    const void* data,
    const void* args,
    BNRSCH_LEN start,
    BNRSCH_LEN end,
    BNRSCH_compareTo comp,
    BNRSCH_access access,
    BNRSCH_LEN* result
){

    BNRSCH_COMP tmpCompRes = 0;
    BNRSCH_LEN middle = start / 2 + end / 2;
    if(start % 2 != 0 && end % 2 != 0) middle++;

    if((end - start + 1) < 3) return 0;
    tmpCompRes = comp(access(datas,middle,args),data,args);
    if(tmpCompRes < 0)      return BNRSCH_find0(datas,data,args,middle,end   ,comp,access,result);
    else if(tmpCompRes > 0) return BNRSCH_find0(datas,data,args,start ,middle,comp,access,result);
    else {
        *result = middle;
        return 1;
    }
    
}

BNRSCH_U1 BNRSCH_find(
    const void* datas,
    const void* data,
    const void* args,
    BNRSCH_LEN start,
    BNRSCH_LEN len,
    BNRSCH_compareTo comp,
    BNRSCH_access access,
    BNRSCH_LEN* result
){
    if(      comp(access(datas,start            ,args),data,args) == 0) {
        *result = start;
        return 1;
    }else if(comp(access(datas,start + (len - 1),args),data,args) == 0) {
        *result = start + (len - 1);
        return 1;
    }
    return BNRSCH_find0(datas,data,args,start,start + (len - 1),comp,access,result);
}