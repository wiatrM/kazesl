<p style="text-align: center;">
<img src="http://1.bp.blogspot.com/-nRSCf2IylGk/T2umGxX7JmI/AAAAAAAAUig/XXHFgT1hj2Q/s1600/kaze.jpg" alt="Kaze-SL">

# Kaze settlement layer
[![Build Status](https://travis-ci.org/kaze-org/kaze-sl.svg?branch=master)](https://travis-ci.org/kaze-org/kaze-sl)
[![Build status](https://ci.appveyor.com/api/projects/status/unyv1q5hlue50io1?svg=true)](https://ci.appveyor.com/project/wiatrM/kaze-sl)
[![codecov](https://codecov.io/gh/kaze-org/kaze-sl/branch/develop/graph/badge.svg)](https://codecov.io/gh/kaze-org/kaze-sl)
[![GitHub (pre-)release](https://img.shields.io/github/release/kaze-org/kaze-sl/all.svg)]()

</p>

## How to run

```
$ git submodule init
$ git submodule update
```

### Run Docker (debug mode wih tests):

$PWD is your working dir

```
docker image pull kazeorg/kazesl
docker run -v "$PWD/:/app:rw" kazeorg/kazesl /bin/bash -c "bash /app/scripts/build.sh --debug --ut"
docker run -v "$PWD/:/app:rw" -p 8080:8080 kazeorg/kazesl /app/build/bin/kazesl-run
```
## Development process

For more information regarding development process please see [Development process](https://github.com/kaze-org/kaze-sl/wiki/Development-process)

## Links

* [Main wiki](https://github.com/kaze-org/kaze-sl/wiki/)
* [Branching strategy](https://github.com/kaze-org/kaze-sl/wiki/Branching-strategy)
