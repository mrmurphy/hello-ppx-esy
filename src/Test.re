open Migrate_parsetree;
open Ast_406;
open Ast_mapper;
open Parsetree;

let expr = (mapper, e) =>
  switch (e.pexp_desc) {
  /* If the expression is [%test] */
  | Pexp_extension(({txt: "test", loc, _}, _payload)) =>
    /* Then replace by 42 */
    Ast_helper.Exp.constant(Pconst_integer("42", None))
  | _ => default_mapper.expr(mapper, e)
  };

let mapper = (_, _) => {...default_mapper, expr};

let () = Driver.register(~name="test", Versions.ocaml_406, mapper);
