### UESTC编译原理课程设计



#####这是一个词法分析器+语法分析器。

​	对code.txt的代码进行分析，并输出错误。如果没有错误生成代码的变量表		和过程表。

要求采用递归下降分析方法。

课程要求的词法与文法描述：

> <程序>→<分程序>
>
> <分程序>→begin<说明语句表><执行语句表>end
>
> <说明语句表>→<说明语句>;│<说明语句表> ；<说明语句>;
>
> <说明语句>→<变量说明>│<函数说明>
>
> <变量说明>→integer<变量>
>
> <变量>→<标识符>
>
> <标识符>→<字母>│<标识符><字母>│<标识符><数字>
>
> <字母>→a│b│c│d│e│f│g│h│i│j│k│l│m│n│o │p│q │r│s│t│u│v│w│x│y│z
>
> <数字>→0│1│2│3│4│5│6│7│8│9
>
> <函数说明>→integer function <标识符>（<参数>）；<函数体>
>
> <参数>→<变量>
>
> <函数体>→begin<说明语句表>；<执行语句表>end
>
> <执行语句表>→<执行语句>│<执行语句表>；<执行语句>
>
> <执行语句>→<读语句>│<写语句>│<赋值语句>│<条件语句>
>
> <读语句>→read(<变量>)
>
> <赋值语句>→<变量>:=<算术表达式>
>
> <算术表达式>→<算术表达式>-<项>│<项>
>
> <项>→<项>*<因子>│<因子>
>
> <因子>→<变量>│<常数>│<函数调用>
>
> <函数调用>-><函数命>(<算术表达式>)
>
> <常数>→<无符号整数>
>
> <写语句>→write(<变量>)
>
> <条件语句>→if<条件表达式>then<执行语句>else<执行语句>
>
> <条件表达式>→<算术表达式><关系运算符><算术表达式>
>
> <关系运算符>→<│<=│>│>=│=│<>





输出要求：

> 变量名表
>
> - 变量名vname:char(16)
> - 所属过程vproc:char(16)
> - 分类vkind:0..1(0—变量、1—形参)
> - 变量类型vtype:types
> - 变量层次vlev:int
> - 变量在变量表中的位置vadr:int(相对第一个变量而言)
>
> 过程名表
>
> - 过程名pname:char(16)
> - 过程类型ptype:types
> - 过程层次plev:int
> - 第一个变量在变量表中的位置fadr:int
> - 最后一个变量在变量表中的位置ladr:int
>
> 错误类型
>
> - 符号缺失
> - 符号重定义或未定义

