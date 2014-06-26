### RCRand
After struggling with a race condition issue for an hour or two, I decided to make use of this wonderful unpredictability that is shared resource mutation.



### Installation

```
git clone git@github.com:dasmithii/RCRand.git
cd RCRand
cmake .
make install
```



### Usage

The `bytes` option specifies an output count.
```
$ rcrand --bytes 5
ȅc!PV
```

By switching on `format`, you can print a more human-readable output.
```
$ rcrand -format --bytes 5
81
90
151
215
186
```

If `bytes` aren't specified, output will continue indefinitely.
```
rcrand -format
142
206
144
242
65
219
81
220
13
204
141
136
...
```
