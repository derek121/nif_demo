#include <stdio.h>
#include "erl_nif.h"

typedef struct {
  int val1;
  int val2;
} Vals;

static void resource_dtor(ErlNifEnv* env, void* obj)
{
  printf("In resource_dtor\r\n");

  /*
  Vals* vals = (Vals *)obj;
  if (vals != NULL) {
    enif_release_resource(vals->entries);
  }
  */
}
static int load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
  printf("In load\r\n");

  ErlNifResourceType *resource_type = enif_open_resource_type(
      env,
      NULL,
      "resource",
      resource_dtor,
      (ErlNifResourceFlags)(ERL_NIF_RT_CREATE),
      NULL
  );

  *priv_data = resource_type;
  return 0;
}

static int upgrade(ErlNifEnv* env, void** priv_data, void** old_priv_data, ERL_NIF_TERM load_info)
{
  printf("In upgrade\r\n");
  return 0;
}

static void unload(ErlNifEnv* env, void* priv_data)
{
  printf("In unload\r\n");
}

/* */
static ERL_NIF_TERM return_int_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  return enif_make_int(env, 24);
}

static ERL_NIF_TERM return_atom_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  return enif_make_atom(env, "hello");
}

static ERL_NIF_TERM return_string_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  return enif_make_string(env, "hello", ERL_NIF_LATIN1);
}

static ERL_NIF_TERM return_tuple_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ERL_NIF_TERM a = enif_make_atom(env, "val");
  ERL_NIF_TERM i = enif_make_int(env, 25);
  return enif_make_tuple2(env, a, i);
}

static ERL_NIF_TERM return_list_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ERL_NIF_TERM i1 = enif_make_int(env, 26);
  ERL_NIF_TERM i2 = enif_make_int(env, 36);
  ERL_NIF_TERM i3 = enif_make_int(env, 46);
  return enif_make_list3(env, i1, i2, i3);
}



/* */

static ERL_NIF_TERM receive_int_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int i;
  if (!enif_get_int(env, argv[0], &i)) {
    return 0;
  }
  printf("Int: %d\r\n", i);

  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM receive_atom_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  unsigned int len;
  if (!enif_get_atom_length(env, argv[0], &len, ERL_NIF_LATIN1)) {
    return 0;
  }
  char *buf = (char *)enif_alloc(len + 1);

  if (!enif_get_atom(env, argv[0], buf, len + 1, ERL_NIF_LATIN1)) {
    return 0;
  }
  printf("Atom: %s\r\n", buf);

  enif_free(buf);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM receive_string_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  unsigned int len;
  if (!enif_get_list_length(env, argv[0], &len)) {
    return 0;
  }
  char *buf = (char *)enif_alloc(len + 1);

  if (!enif_get_string(env, argv[0], buf, len + 1, ERL_NIF_LATIN1)) {
    return 0;
  }
  printf("String: %s\r\n", buf);

  enif_free(buf);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM receive_tuple_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  const ERL_NIF_TERM *tuple;
  int arity;
  if (!enif_get_tuple(env, argv[0], &arity, &tuple)) {
    return enif_make_badarg(env);
  }

  for (int i = 0; i < arity; i++) {
    int val;
    if (!enif_get_int(env, tuple[i], &val)) {
      return enif_make_badarg(env);
    }
    printf("Val %d: %d\r\n", i, val);
  }

  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM receive_list_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ERL_NIF_TERM head, tail;
  int val;
  ERL_NIF_TERM list = argv[0];

  while (enif_get_list_cell(env, list, &head, &tail)) {
    if (!enif_get_int(env, head, &val)) {
      return enif_make_badarg(env);
    }
    printf("Val: %d\r\n", val);
    list = tail;
  }

  return enif_make_atom(env, "ok");
}




/* */

static ERL_NIF_TERM return_resource_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ErlNifResourceType* resource_type = (ErlNifResourceType*)enif_priv_data(env);

  Vals *vals = (Vals *)enif_alloc_resource(resource_type, sizeof(Vals));
  vals->val1 = 23;
  vals->val2 = 25;

  ERL_NIF_TERM result = enif_make_resource(env, vals);
  enif_release_resource(vals);
  return result;
}

static ERL_NIF_TERM receive_resource_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ErlNifResourceType* resource_type = (ErlNifResourceType*)enif_priv_data(env);

  void *v;
  if (!enif_get_resource(env, argv[0], resource_type, &v)) {
    return 0;
  }
  Vals *vals = (Vals *)v;

  printf("val1: %d\r\n", vals->val1);
  printf("val2: %d\r\n", vals->val2);

  return enif_make_atom(env, "ok");
}



/* */
static ERL_NIF_TERM test_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  ErlNifSysInfo info;
  enif_system_info(&info, sizeof(info));
  printf("TEST: "
  "driver_major_version: %d. "
  "driver_minor_version: %d. "
  "erts_version: %s. "
  "otp_release: %s. "
  "thread_support: %d. "
  "smp_support: %d. "
  "async_threads: %d. "
  "scheduler_threads: %d. "
  "nif_major_version: %d. "
  "nif_minor_version: %d. "
  "dirty_scheduler_support: %d. "
  "\r\n",
      info.driver_major_version,
      info.driver_minor_version,
      info.erts_version,
      info.otp_release,
      info.thread_support,
      info.smp_support,
      info.async_threads,
      info.scheduler_threads,
      info.nif_major_version,
      info.nif_minor_version,
      info.dirty_scheduler_support);

  return enif_make_atom(env, "ok");
}




static ErlNifFunc nif_funcs[] = {
  {"return_int", 0, return_int_nif},
  {"return_atom", 0, return_atom_nif},
  {"return_string", 0, return_string_nif},
  {"return_tuple", 0, return_tuple_nif},
  {"return_list", 0, return_list_nif},

  {"receive_int", 1, receive_int_nif},
  {"receive_atom", 1, receive_atom_nif},
  {"receive_string", 1, receive_string_nif},
  {"receive_tuple", 1, receive_tuple_nif},
  {"receive_list", 1, receive_list_nif},

  {"return_resource", 0, return_resource_nif},
  {"receive_resource", 1, receive_resource_nif},

  {"test", 0, test_nif},
};

ERL_NIF_INIT(demo, nif_funcs, load, NULL, upgrade, unload)

