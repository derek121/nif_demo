#include <stdio.h>
#include "erl_nif.h"

static ERL_NIF_TERM hello_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  return enif_make_tuple2(env,
    enif_make_atom(env, "ok"),
    enif_make_atom(env, "joe"));
}

static ErlNifFunc nif_funcs[] = {
  {"hello", 0, hello_nif}
};

ERL_NIF_INIT(minimal, nif_funcs, NULL, NULL, NULL, NULL)

