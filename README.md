# NIF Demo
Examples of Erlang NIFs.

## Use
rebar must be in your path. See <https://github.com/rebar/rebar> for details.

```
$ git clone https://github.com/derek121/nif_demo.git
$ cd nif_demo
$ make && make run
...
1> minimal:hello().
{ok,joe}
2> demo:return_int().
24
3> demo:receive_tuple({22, 23}). 
Val 0: 22
Val 1: 23
ok
```

## References
* [Presentation slide deck](https://github.com/derek121/nif_demo/blob/master/meetup-nifs.pdf)
* <http://www.erlang.org/doc/tutorial/nif.html>
* <http://www.erlang.org/doc/man/erl_nif.html>
* <https://github.com/vinoski/erlsha2>
* <https://github.com/vinoski/bitwise>
* [Steve Vinoski's 2014 Codemesh talk on schedulers](http://www.codemesh.io/codemesh2014/steve-vinoski)

