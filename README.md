# Better Integral Constant (BIC)

A header-only library providing a `Fixed` type which represents a compile-time fixed constant (similar to integral constant).
A `Fixed` can be implicitly converted to the underlying type and supports arithmetic, logical and comparaison operators.
Obviously arithmetic operations between two `Fixed` returns a `Fixed`.

```cpp
 BIC::Fixed<int, 2> a; 
 BIC::Fixed<int, 3> b; 
    
 static_assert( ((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false> == false); 
 static_assert( BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>));
 static_assert( BIC::isFixed(BIC::isFixed(((a + BIC::fixed<long,1>) <= b) and BIC::fixed<bool, false>))); 
```

`BIC` Is inteneded to help the compiler optimizing kernels

```cpp
template<typename Alpha, typename Scalar, typename Size>
void axpy(const Alpha alpha, const Scalar* x, const Size N, Scalar* y)
{
  // Size may be a BIC::Fixed so we iterate with a 
  // BIC::Mutable<Size> 
  for (BIC::Mutable<Size> i=0; i!=N; ++i)
  {
    y[i] += alpha*x[i];
  }
}
```
Our kernel can be called with either native types or `BIC::Fixed`:
```cpp
	constexpr size_t N = 20;
	
	std::vector<double> x(N, 1);
	std::vector<double> y(N, 2);
	
	axpy(1, x.data(), N, y.data()); 
	axpy(BIC::fixed<double,1.>, x.data(), BIC::fixed<size_t, N>, y.data());
```
Let us look at the asm corresponding to the two Kernels:
```asm
void axpy<int, double, int>(int, double const*, int, double*):
        mov     eax, edi
        movsx   rdi, edx
        test    edi, edi
        je      .L398
        pxor    xmm2, xmm2
        cvtsi2sd        xmm2, eax
        cmp     edi, 1
        je      .L400
        mov     rax, rcx
        sub     rax, rsi
        cmp     rax, 8
        je      .L400
        mov     edx, edi
        movapd  xmm1, xmm2
        xor     eax, eax
        shr     edx
        unpcklpd        xmm1, xmm1
        sal     rdx, 4
.L401:
        movupd  xmm0, XMMWORD PTR [rsi+rax]
        movupd  xmm3, XMMWORD PTR [rcx+rax]
        mulpd   xmm0, xmm1
        addpd   xmm0, xmm3
        movups  XMMWORD PTR [rcx+rax], xmm0
        add     rax, 16
        cmp     rdx, rax
        jne     .L401
        mov     eax, edi
        and     eax, -2
        and     edi, 1
        je      .L398
        cdqe
        mulsd   xmm2, QWORD PTR [rsi+rax*8]
        addsd   xmm2, QWORD PTR [rcx+rax*8]
        movsd   QWORD PTR [rcx+rax*8], xmm2
        ret
.L400:
        sal     rdi, 3
        xor     eax, eax
.L405:
        movsd   xmm0, QWORD PTR [rsi+rax]
        mulsd   xmm0, xmm2
        addsd   xmm0, QWORD PTR [rcx+rax]
        movsd   QWORD PTR [rcx+rax], xmm0
        add     rax, 8
        cmp     rdi, rax
        jne     .L405
.L398:
        ret
void axpy<ic::Fixed<double, 0x1p+0>, double, ic::Fixed<unsigned long, 10ul>>(ic::Fixed<double, 0x1p+0>, double const*, ic::Fixed<unsigned long, 10ul>, double*):
        mov     rax, rsi
        sub     rax, rdi
        cmp     rax, 8
        je      .L416
        movupd  xmm0, XMMWORD PTR [rdi]
        movupd  xmm1, XMMWORD PTR [rsi]
        movupd  xmm2, XMMWORD PTR [rsi+16]
        movupd  xmm3, XMMWORD PTR [rsi+32]
        addpd   xmm0, xmm1
        movupd  xmm4, XMMWORD PTR [rsi+48]
        movupd  xmm5, XMMWORD PTR [rsi+64]
        movups  XMMWORD PTR [rsi], xmm0
        movupd  xmm0, XMMWORD PTR [rdi+16]
        addpd   xmm0, xmm2
        movups  XMMWORD PTR [rsi+16], xmm0
        movupd  xmm0, XMMWORD PTR [rdi+32]
        addpd   xmm0, xmm3
        movups  XMMWORD PTR [rsi+32], xmm0
        movupd  xmm0, XMMWORD PTR [rdi+48]
        addpd   xmm0, xmm4
        movups  XMMWORD PTR [rsi+48], xmm0
        movupd  xmm0, XMMWORD PTR [rdi+64]
        addpd   xmm0, xmm5
        movups  XMMWORD PTR [rsi+64], xmm0
        ret
.L416:
        movsd   xmm0, QWORD PTR [rsi]
        addsd   xmm0, QWORD PTR [rdi]
        movsd   QWORD PTR [rsi], xmm0
        movsd   xmm0, QWORD PTR [rsi+8]
        addsd   xmm0, QWORD PTR [rdi+8]
        movsd   QWORD PTR [rsi+8], xmm0
        movsd   xmm0, QWORD PTR [rsi+16]
        addsd   xmm0, QWORD PTR [rdi+16]
        movsd   QWORD PTR [rsi+16], xmm0
        movsd   xmm0, QWORD PTR [rsi+24]
        addsd   xmm0, QWORD PTR [rdi+24]
        movsd   QWORD PTR [rsi+24], xmm0
        movsd   xmm0, QWORD PTR [rsi+32]
        addsd   xmm0, QWORD PTR [rdi+32]
        movsd   QWORD PTR [rsi+32], xmm0
        movsd   xmm0, QWORD PTR [rsi+40]
        addsd   xmm0, QWORD PTR [rdi+40]
        movsd   QWORD PTR [rsi+40], xmm0
        movsd   xmm0, QWORD PTR [rsi+48]
        addsd   xmm0, QWORD PTR [rdi+48]
        movsd   QWORD PTR [rsi+48], xmm0
        movsd   xmm0, QWORD PTR [rsi+56]
        addsd   xmm0, QWORD PTR [rdi+56]
        movsd   QWORD PTR [rsi+56], xmm0
        movsd   xmm0, QWORD PTR [rsi+64]
        addsd   xmm0, QWORD PTR [rdi+64]
        movsd   QWORD PTR [rsi+64], xmm0
        movsd   xmm0, QWORD PTR [rsi+72]
        addsd   xmm0, QWORD PTR [rdi+72]
        movsd   QWORD PTR [rsi+72], xmm0
        ret
```
Note that:

- The for loop has been complitly rmoved by the compiler
- There is no longer `mulsd` or `mulpd` since the compiler knows it need to multiply a number by 1.
