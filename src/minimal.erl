-module(minimal).

-export([hello/0]).

-on_load(init/0).

init() ->
  ok = erlang:load_nif("priv/minimal_nif", 0).

hello() ->
  erlang:nif_error(nif_not_loaded).

