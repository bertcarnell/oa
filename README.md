oa
==

Orthogonal Arrays based on Owen from Statlib.  Still available [here](http://ftp.uni-bayreuth.de/math/statlib/designs/)

### Status

|<sub>Linux & MacOS</sub>|<sub>Windows</sub>|<sub>Code Coverage</sub>|
|:---:|:---:|:---:|
|[![Build Status](https://www.travis-ci.org/bertcarnell/oa.svg?branch=master)](https://www.travis-ci.org/bertcarnell/oa)|[![Build status](https://ci.appveyor.com/api/projects/status/c25m7jk7ltx3ovs0?svg=true)](https://ci.appveyor.com/project/bertcarnell/oa)|[![codecov](https://codecov.io/gh/bertcarnell/oa/branch/master/graph/badge.svg)](https://codecov.io/gh/bertcarnell/oa)|

### Documentation

[Doxygen](http://bertcarnell.github.io/oa/html/index.html)

### Examples

Notes are from Owen.

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
