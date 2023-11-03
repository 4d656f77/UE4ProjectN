> # Project N UE4

> ## Class Index
> 
> - [clientSocket](#clientSocket-Class)
> - [KISA SHA 256](#KISA-SHA-256)

# clientSocket Class

> - 목적
>   
>   클라이언트에서 소켓을 관리할 수 있는 클래스
> 
> - 특징
>   
>   `FRunnable` 객체를 상속 받아서 별도의 스레드를 이용해 소켓을 사용한다.
> 
> - 



# KISA SHA 256

> - 비밀번호 해싱을 위한 모듈 추가
> 
> - 추가 중 문제 발생
> 
> ![errorC2040typedef](https://github.com/4d656f77/UE4ProjectN/blob/master/images/errorC2040typedef.png?raw=true)
> 
> `ULONG`은 `minwindef.h`에 별칭이 붙어있고, `ULONG_PTR`은 `basetsd.h`에 다음과 같이 별칭이 붙어 있다.
> 
> `typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;`
