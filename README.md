oa
==

Orthogonal Arrays based on Owen from Statlib.  Still available [here](http://ftp.uni-bayreuth.de/math/statlib/designs/)

### Status

|<sub>Linux & MacOS</sub>|<sub>Windows</sub>|<sub>Code Coverage</sub>|<sub>Github Actions</sub>|<sub>Github CodeQL</sub>|
|:---:|:---:|:---:|:---:|:---:|
|[![Build Status](https://www.travis-ci.org/bertcarnell/oa.svg?branch=master)](https://www.travis-ci.org/bertcarnell/oa)|[![Build status](https://ci.appveyor.com/api/projects/status/c25m7jk7ltx3ovs0?svg=true)](https://ci.appveyor.com/project/bertcarnell/oa)|[![codecov](https://codecov.io/gh/bertcarnell/oa/branch/master/graph/badge.svg)](https://codecov.io/gh/bertcarnell/oa)|![CMake](https://github.com/bertcarnell/oa/workflows/CMake/badge.svg)|![CodeQL](https://github.com/bertcarnell/oa/workflows/CodeQL/badge.svg)|

### Documentation

[Doxygen](http://bertcarnell.github.io/oa/html/index.html)

### Examples

Notes on each orthogonal array are from [Owen](http://ftp.uni-bayreuth.de/math/statlib/designs/).

#### Addelman-Kempthorne (addelkemp)

The `addelkemp` program produces `OA( 2q^2, k, q, 2 )`,  `k <= 2q+1`,
for odd prime powers `q`.  Even prime powers may be produced using
`bosebush`.

```c
int q = 2;
int ncol = 2*q;
int n = 2*q*q;
oacpp::COrthogonalArray coa;
coa.addelkemp(q, ncol, &n);
coa.getoa();
```

#### Addelman-Kempethorn (addelkemp3)

The `addelkemp3` program produces `OA( 2\*q^3, k, q, 2 )`,  `k <= 2q^2+2q+1`,
for prime powers `q`.  `q` may be an odd prime power, or `q` may
be `2` or `4`.

```c
int q = 3;
int ncol = 2*q*q + 2*q + 1;
int n;
oacpp::COrthogonalArray coa;
coa.addelkemp3(q, ncol, &n);
coa.getoa();
```

#### Bose

The `bose` program produces `OA( q^2, k, q, 2 )`,  `k <= q+1`
for prime powers `q`.

```c
int q = 2;
int ncol = q;
int n = 0;
oacpp::COrthogonalArray coa;
coa.bose(q, ncol, &n);
coa.getoa();
```

#### Bose-Bush

The `bosebush` program produces `OA( 2q^2, k, q, 2 )`,  `k <= 2q+1`,
for powers of `2`, `q=2^r`.

```c
int q = 8;
int ncol = 5;
int n = 0;
oacpp::COrthogonalArray coa;
coa.bosebush(q, ncol, &n);
coa.getoa();
```

#### Bush

The `bush` program produces `OA( q^3, k, q, 3 )`,  `k <= q+1`
for prime powers `q`.

```c
int q = 3;
int ncol = 3;
int n = 0;
oacpp::COrthogonalArray coa;
coa.bush(q, ncol, &n);
coa.getoa();
```

#### Bose-Bush lambda

The `bosebushl` program produces `OA( lambda*q^2, k, q, 2 )`,  
`k <= lambda*q+1`, for prime powers `q` and `lambda > 1`.  Both `q` and 
`lambda` must be powers of the same prime.

```c
int q = 2;
int ncol = q;
int lambda = 2;
int n = 0;
oacpp::COrthogonalArray coa;
coa.bosebushl(lambda, q, ncol, &n);
coa.getoa();
```

#### Bush t

The `bush` program produces `OA( q^t, k, q, t )`,  `k <= q+1`, `t>=3`,
for prime powers `q`.

```c
int q = 3;
int ncol = 3;
int str = 2;
int n = 0;
oacpp::COrthogonalArray coa;
coa.busht(str, q, ncol, &n);
coa.getoa();
```
