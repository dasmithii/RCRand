### RCRand
After struggling with a race condition issue for an hour or two, I decided to make use of this wonderful unpredictability that is shared resource mutation.

![](https://raw.githubusercontent.com/dasmithii/RCRand/master/img/bytemap.png =230x230)

Here's the (summarized) algorithm.

###### (1) Setup
+ Obtain a byte buffer unix rand(). This serves as a starting point for the output sequence.
+ Spawn a thread pool.

###### (2) Generation
+ Have each worker thread mutate the byte buffer concurrently, without any mutex locks or et cetera.
+ For each byte generation request, XOR all bytes in the buffer and return the result. During this time, worker threads continue.
+ Ensure that at least one operation has been performed on the buffer between each byte output.

###### (3) Tear-down
+ Cancel all worker threads.



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