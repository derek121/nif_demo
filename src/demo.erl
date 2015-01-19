-module(demo).

-export([return_int/0]).
-export([return_atom/0]).
-export([return_string/0]).
-export([return_tuple/0]).
-export([return_list/0]).

-export([receive_int/1]).
-export([receive_atom/1]).
-export([receive_string/1]).
-export([receive_tuple/1]).
-export([receive_list/1]).

-export([return_resource/0]).
-export([receive_resource/1]).

-on_load(init/0).

init() ->
  ok = erlang:load_nif("priv/demo_nif", 0).

return_int() ->
  erlang:nif_error(nif_not_loaded).

return_atom() ->
  erlang:nif_error(nif_not_loaded).

return_string() ->
  erlang:nif_error(nif_not_loaded).

return_tuple() ->
  erlang:nif_error(nif_not_loaded).

return_list() ->
  erlang:nif_error(nif_not_loaded).

%%%
receive_int(_Val) ->
  erlang:nif_error(nif_not_loaded).

receive_atom(_Val) ->
  erlang:nif_error(nif_not_loaded).

receive_string(_Val) ->
  erlang:nif_error(nif_not_loaded).

receive_tuple(_Val) ->
  erlang:nif_error(nif_not_loaded).

receive_list(_Val) ->
  erlang:nif_error(nif_not_loaded).

%%%
return_resource() ->
  erlang:nif_error(nif_not_loaded).

receive_resource(_Val) ->
  erlang:nif_error(nif_not_loaded).

