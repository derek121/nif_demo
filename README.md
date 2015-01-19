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
