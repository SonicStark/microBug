# microBug

A concise, flexible, path- and bug-rich program is helpful for debugging those fuzzers under development. 

After adding some new features to a fuzzer, we need to verify if it works as expect. Usually *Unit Test* is a good choice. You can also attach a debugger to the fuzzer process for a quick view, but waiting until a breakpoint is hit 2000 YEARS LATER would be a nightmare. Then `microBug` is here to help, which is easy to be explored by most fuzzers.

What's more, `microBug` can be built into various versions. It is helpful when you debug some tools related with symbols and [sanitizers](https://github.com/google/sanitizers) (i.e. a [Pin tool](https://software.intel.com/sites/landingpage/pintool/docs/98650/Pin/doc/html/index.html)).

To build `microBug`, use `build.sh`. The binaries will locate at `build/`.

If `argc > 1`, it will try to use the last parameter as the path of input file. If fails to open, it will read from `stdin` as a fallback method. If `argc <= 1`, it will read input from `stdin`. If you see `[+] Accepting input from '[STDIN]'` when running the target manually, you should press <kbd>CTRL</kbd>+<kbd>D</kbd> to send `EOF` after typing your things. Otherwise it would continue to receive input because there is no `EOF` to close `stdin`.

Testcases locate at `./corpus`:
 * `./corpus/norm/` - normal, not trigger any vulnerabilities
 * `./corpus/wiki/` - trigger vulnerabilities in `wiki_*`
 * `./corpus/hits/` - trigger vulnerabilities in `hit_*`