#include "quickjs.h"
    
#include "raylib.h"
#include "rcamera.h"

static float TextToFloat(const char *text)
{
    float value = 0.0f;
    float sign = 1.0f;

    if ((text[0] == '+') || (text[0] == '-'))
    {
        if (text[0] == '-') sign = -1.0f;
        text++;
    }

    int i = 0;
    for (; ((text[i] >= '0') && (text[i] <= '9')); i++) value = value*10.0f + (float)(text[i] - '0');

    if (text[i++] != '.') value *= sign;
    else
    {
        float divisor = 10.0f;
        for (; ((text[i] >= '0') && (text[i] <= '9')); i++)
        {
            value += ((float)(text[i] - '0'))/divisor;
            divisor = divisor*10.0f;
        }
    }

    return value;
}
    
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

enum {
    __JS_ATOM_NULL = JS_ATOM_NULL,
#define DEF(name, str) JS_ATOM_ ## name,
#include "quickjs-atom.h"
#undef DEF
    JS_ATOM_END,
};

#include <emscripten.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))



static JSClassID js_Vector2_class_id;

static JSValue js_Vector2_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Vector2 *s = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewFloat64(ctx, (double) s->x);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->y);
}


    return JS_UNDEFINED;
}

static JSValue js_Vector2_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Vector2 *s = JS_GetOpaque2(ctx, this_val, js_Vector2_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    double v0;
    if (JS_ToFloat64(ctx, &v0, val))
        return JS_EXCEPTION;
    s->x = (float) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->y = (float) v1;
}

    
    return JS_UNDEFINED;
}

static void js_Vector2_finalizer(JSRuntime *rt, JSValue val)
{
    Vector2 *s = JS_GetOpaque(val, js_Vector2_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Vector2_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Vector2_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Vector2 *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
double v0;
if (JS_ToFloat64(ctx, &v0, argv[0]))
        goto fail;
s->x = (float) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->y = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Vector2_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Vector2_class = {
    "Vector2",
    .finalizer = js_Vector2_finalizer,
};

static const JSCFunctionListEntry js_Vector2_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("x", js_Vector2_get, js_Vector2_set, 0),
    JS_CGETSET_MAGIC_DEF("y", js_Vector2_get, js_Vector2_set, 1),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Vector2", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Vector2(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Vector2_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Vector2_class_id, &js_Vector2_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Vector2_proto_funcs, countof(js_Vector2_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Vector2_ctor, "Vector2", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Vector2_class_id, proto);

    JS_SetModuleExport(ctx, m, "Vector2", class);
    return 0;
}



static JSClassID js_Vector3_class_id;

static JSValue js_Vector3_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Vector3 *s = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewFloat64(ctx, (double) s->x);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->y);
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->z);
}


    return JS_UNDEFINED;
}

static JSValue js_Vector3_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Vector3 *s = JS_GetOpaque2(ctx, this_val, js_Vector3_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    double v0;
    if (JS_ToFloat64(ctx, &v0, val))
        return JS_EXCEPTION;
    s->x = (float) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->y = (float) v1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->z = (float) v2;
}

    
    return JS_UNDEFINED;
}

static void js_Vector3_finalizer(JSRuntime *rt, JSValue val)
{
    Vector3 *s = JS_GetOpaque(val, js_Vector3_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Vector3_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Vector3_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Vector3 *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
double v0;
if (JS_ToFloat64(ctx, &v0, argv[0]))
        goto fail;
s->x = (float) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->y = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->z = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Vector3_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Vector3_class = {
    "Vector3",
    .finalizer = js_Vector3_finalizer,
};

static const JSCFunctionListEntry js_Vector3_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("x", js_Vector3_get, js_Vector3_set, 0),
    JS_CGETSET_MAGIC_DEF("y", js_Vector3_get, js_Vector3_set, 1),
    JS_CGETSET_MAGIC_DEF("z", js_Vector3_get, js_Vector3_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Vector3", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Vector3(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Vector3_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Vector3_class_id, &js_Vector3_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Vector3_proto_funcs, countof(js_Vector3_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Vector3_ctor, "Vector3", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Vector3_class_id, proto);

    JS_SetModuleExport(ctx, m, "Vector3", class);
    return 0;
}



static JSClassID js_Vector4_class_id;

static JSValue js_Vector4_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Vector4 *s = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewFloat64(ctx, (double) s->x);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->y);
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->z);
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->w);
}


    return JS_UNDEFINED;
}

static JSValue js_Vector4_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Vector4 *s = JS_GetOpaque2(ctx, this_val, js_Vector4_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    double v0;
    if (JS_ToFloat64(ctx, &v0, val))
        return JS_EXCEPTION;
    s->x = (float) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->y = (float) v1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->z = (float) v2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->w = (float) v3;
}

    
    return JS_UNDEFINED;
}

static void js_Vector4_finalizer(JSRuntime *rt, JSValue val)
{
    Vector4 *s = JS_GetOpaque(val, js_Vector4_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Vector4_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Vector4_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Vector4 *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
double v0;
if (JS_ToFloat64(ctx, &v0, argv[0]))
        goto fail;
s->x = (float) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->y = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->z = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->w = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Vector4_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Vector4_class = {
    "Vector4",
    .finalizer = js_Vector4_finalizer,
};

static const JSCFunctionListEntry js_Vector4_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("x", js_Vector4_get, js_Vector4_set, 0),
    JS_CGETSET_MAGIC_DEF("y", js_Vector4_get, js_Vector4_set, 1),
    JS_CGETSET_MAGIC_DEF("z", js_Vector4_get, js_Vector4_set, 2),
    JS_CGETSET_MAGIC_DEF("w", js_Vector4_get, js_Vector4_set, 3),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Vector4", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Vector4(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Vector4_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Vector4_class_id, &js_Vector4_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Vector4_proto_funcs, countof(js_Vector4_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Vector4_ctor, "Vector4", 4, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Vector4_class_id, proto);

    JS_SetModuleExport(ctx, m, "Vector4", class);
    return 0;
}



static JSClassID js_Quaternion_class_id;

static JSValue js_Quaternion_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Quaternion *s = JS_GetOpaque2(ctx, this_val, js_Quaternion_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewFloat64(ctx, (double) s->x);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->y);
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->z);
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->w);
}


    return JS_UNDEFINED;
}

static JSValue js_Quaternion_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Quaternion *s = JS_GetOpaque2(ctx, this_val, js_Quaternion_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    double v0;
    if (JS_ToFloat64(ctx, &v0, val))
        return JS_EXCEPTION;
    s->x = (float) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->y = (float) v1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->z = (float) v2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->w = (float) v3;
}

    
    return JS_UNDEFINED;
}

static void js_Quaternion_finalizer(JSRuntime *rt, JSValue val)
{
    Quaternion *s = JS_GetOpaque(val, js_Quaternion_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Quaternion_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Quaternion_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Quaternion *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
double v0;
if (JS_ToFloat64(ctx, &v0, argv[0]))
        goto fail;
s->x = (float) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->y = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->z = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->w = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Quaternion_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Quaternion_class = {
    "Quaternion",
    .finalizer = js_Quaternion_finalizer,
};

static const JSCFunctionListEntry js_Quaternion_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("x", js_Quaternion_get, js_Quaternion_set, 0),
    JS_CGETSET_MAGIC_DEF("y", js_Quaternion_get, js_Quaternion_set, 1),
    JS_CGETSET_MAGIC_DEF("z", js_Quaternion_get, js_Quaternion_set, 2),
    JS_CGETSET_MAGIC_DEF("w", js_Quaternion_get, js_Quaternion_set, 3),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Quaternion", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Quaternion(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Quaternion_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Quaternion_class_id, &js_Quaternion_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Quaternion_proto_funcs, countof(js_Quaternion_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Quaternion_ctor, "Quaternion", 4, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Quaternion_class_id, proto);

    JS_SetModuleExport(ctx, m, "Quaternion", class);
    return 0;
}



static JSClassID js_Matrix_class_id;

static JSValue js_Matrix_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Matrix *s = JS_GetOpaque2(ctx, this_val, js_Matrix_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewFloat64(ctx, (double) s->m0);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->m4);
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->m8);
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->m12);
}

if (magic == 4) {
    return JS_NewFloat64(ctx, (double) s->m1);
}

if (magic == 5) {
    return JS_NewFloat64(ctx, (double) s->m5);
}

if (magic == 6) {
    return JS_NewFloat64(ctx, (double) s->m9);
}

if (magic == 7) {
    return JS_NewFloat64(ctx, (double) s->m13);
}

if (magic == 8) {
    return JS_NewFloat64(ctx, (double) s->m2);
}

if (magic == 9) {
    return JS_NewFloat64(ctx, (double) s->m6);
}

if (magic == 10) {
    return JS_NewFloat64(ctx, (double) s->m10);
}

if (magic == 11) {
    return JS_NewFloat64(ctx, (double) s->m14);
}

if (magic == 12) {
    return JS_NewFloat64(ctx, (double) s->m3);
}

if (magic == 13) {
    return JS_NewFloat64(ctx, (double) s->m7);
}

if (magic == 14) {
    return JS_NewFloat64(ctx, (double) s->m11);
}

if (magic == 15) {
    return JS_NewFloat64(ctx, (double) s->m15);
}


    return JS_UNDEFINED;
}

static JSValue js_Matrix_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Matrix *s = JS_GetOpaque2(ctx, this_val, js_Matrix_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    double v0;
    if (JS_ToFloat64(ctx, &v0, val))
        return JS_EXCEPTION;
    s->m0 = (float) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->m4 = (float) v1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->m8 = (float) v2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->m12 = (float) v3;
}

if (magic == 4) {
    double v4;
    if (JS_ToFloat64(ctx, &v4, val))
        return JS_EXCEPTION;
    s->m1 = (float) v4;
}

if (magic == 5) {
    double v5;
    if (JS_ToFloat64(ctx, &v5, val))
        return JS_EXCEPTION;
    s->m5 = (float) v5;
}

if (magic == 6) {
    double v6;
    if (JS_ToFloat64(ctx, &v6, val))
        return JS_EXCEPTION;
    s->m9 = (float) v6;
}

if (magic == 7) {
    double v7;
    if (JS_ToFloat64(ctx, &v7, val))
        return JS_EXCEPTION;
    s->m13 = (float) v7;
}

if (magic == 8) {
    double v8;
    if (JS_ToFloat64(ctx, &v8, val))
        return JS_EXCEPTION;
    s->m2 = (float) v8;
}

if (magic == 9) {
    double v9;
    if (JS_ToFloat64(ctx, &v9, val))
        return JS_EXCEPTION;
    s->m6 = (float) v9;
}

if (magic == 10) {
    double v10;
    if (JS_ToFloat64(ctx, &v10, val))
        return JS_EXCEPTION;
    s->m10 = (float) v10;
}

if (magic == 11) {
    double v11;
    if (JS_ToFloat64(ctx, &v11, val))
        return JS_EXCEPTION;
    s->m14 = (float) v11;
}

if (magic == 12) {
    double v12;
    if (JS_ToFloat64(ctx, &v12, val))
        return JS_EXCEPTION;
    s->m3 = (float) v12;
}

if (magic == 13) {
    double v13;
    if (JS_ToFloat64(ctx, &v13, val))
        return JS_EXCEPTION;
    s->m7 = (float) v13;
}

if (magic == 14) {
    double v14;
    if (JS_ToFloat64(ctx, &v14, val))
        return JS_EXCEPTION;
    s->m11 = (float) v14;
}

if (magic == 15) {
    double v15;
    if (JS_ToFloat64(ctx, &v15, val))
        return JS_EXCEPTION;
    s->m15 = (float) v15;
}

    
    return JS_UNDEFINED;
}

static void js_Matrix_finalizer(JSRuntime *rt, JSValue val)
{
    Matrix *s = JS_GetOpaque(val, js_Matrix_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Matrix_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Matrix_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Matrix *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
double v0;
if (JS_ToFloat64(ctx, &v0, argv[0]))
        goto fail;
s->m0 = (float) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->m4 = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->m8 = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->m12 = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

double v4;
if (JS_ToFloat64(ctx, &v4, argv[4]))
        goto fail;
s->m1 = (float) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

double v5;
if (JS_ToFloat64(ctx, &v5, argv[5]))
        goto fail;
s->m5 = (float) v5;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 5 = %lf", s->5);*/
        

double v6;
if (JS_ToFloat64(ctx, &v6, argv[6]))
        goto fail;
s->m9 = (float) v6;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 6 = %lf", s->6);*/
        

double v7;
if (JS_ToFloat64(ctx, &v7, argv[7]))
        goto fail;
s->m13 = (float) v7;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 7 = %lf", s->7);*/
        

double v8;
if (JS_ToFloat64(ctx, &v8, argv[8]))
        goto fail;
s->m2 = (float) v8;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 8 = %lf", s->8);*/
        

double v9;
if (JS_ToFloat64(ctx, &v9, argv[9]))
        goto fail;
s->m6 = (float) v9;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 9 = %lf", s->9);*/
        

double v10;
if (JS_ToFloat64(ctx, &v10, argv[10]))
        goto fail;
s->m10 = (float) v10;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 10 = %lf", s->10);*/
        

double v11;
if (JS_ToFloat64(ctx, &v11, argv[11]))
        goto fail;
s->m14 = (float) v11;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 11 = %lf", s->11);*/
        

double v12;
if (JS_ToFloat64(ctx, &v12, argv[12]))
        goto fail;
s->m3 = (float) v12;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 12 = %lf", s->12);*/
        

double v13;
if (JS_ToFloat64(ctx, &v13, argv[13]))
        goto fail;
s->m7 = (float) v13;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 13 = %lf", s->13);*/
        

double v14;
if (JS_ToFloat64(ctx, &v14, argv[14]))
        goto fail;
s->m11 = (float) v14;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 14 = %lf", s->14);*/
        

double v15;
if (JS_ToFloat64(ctx, &v15, argv[15]))
        goto fail;
s->m15 = (float) v15;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 15 = %lf", s->15);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Matrix_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Matrix_class = {
    "Matrix",
    .finalizer = js_Matrix_finalizer,
};

static const JSCFunctionListEntry js_Matrix_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("m0", js_Matrix_get, js_Matrix_set, 0),
    JS_CGETSET_MAGIC_DEF("m4", js_Matrix_get, js_Matrix_set, 1),
    JS_CGETSET_MAGIC_DEF("m8", js_Matrix_get, js_Matrix_set, 2),
    JS_CGETSET_MAGIC_DEF("m12", js_Matrix_get, js_Matrix_set, 3),
    JS_CGETSET_MAGIC_DEF("m1", js_Matrix_get, js_Matrix_set, 4),
    JS_CGETSET_MAGIC_DEF("m5", js_Matrix_get, js_Matrix_set, 5),
    JS_CGETSET_MAGIC_DEF("m9", js_Matrix_get, js_Matrix_set, 6),
    JS_CGETSET_MAGIC_DEF("m13", js_Matrix_get, js_Matrix_set, 7),
    JS_CGETSET_MAGIC_DEF("m2", js_Matrix_get, js_Matrix_set, 8),
    JS_CGETSET_MAGIC_DEF("m6", js_Matrix_get, js_Matrix_set, 9),
    JS_CGETSET_MAGIC_DEF("m10", js_Matrix_get, js_Matrix_set, 10),
    JS_CGETSET_MAGIC_DEF("m14", js_Matrix_get, js_Matrix_set, 11),
    JS_CGETSET_MAGIC_DEF("m3", js_Matrix_get, js_Matrix_set, 12),
    JS_CGETSET_MAGIC_DEF("m7", js_Matrix_get, js_Matrix_set, 13),
    JS_CGETSET_MAGIC_DEF("m11", js_Matrix_get, js_Matrix_set, 14),
    JS_CGETSET_MAGIC_DEF("m15", js_Matrix_get, js_Matrix_set, 15),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Matrix", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Matrix(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Matrix_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Matrix_class_id, &js_Matrix_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Matrix_proto_funcs, countof(js_Matrix_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Matrix_ctor, "Matrix", 16, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Matrix_class_id, proto);

    JS_SetModuleExport(ctx, m, "Matrix", class);
    return 0;
}



static JSClassID js_Color_class_id;

static JSValue js_Color_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Color *s = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->r);
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->g);
}

if (magic == 2) {
    return JS_NewUint32(ctx, (unsigned int) s->b);
}

if (magic == 3) {
    return JS_NewUint32(ctx, (unsigned int) s->a);
}


    return JS_UNDEFINED;
}

static JSValue js_Color_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Color *s = JS_GetOpaque2(ctx, this_val, js_Color_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->r = (unsigned char) v0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->g = (unsigned char) v1;
}

if (magic == 2) {
    unsigned int v2;
    if (JS_ToUint32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->b = (unsigned char) v2;
}

if (magic == 3) {
    unsigned int v3;
    if (JS_ToUint32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->a = (unsigned char) v3;
}

    
    return JS_UNDEFINED;
}

static void js_Color_finalizer(JSRuntime *rt, JSValue val)
{
    Color *s = JS_GetOpaque(val, js_Color_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Color_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Color_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Color *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->r = (unsigned char) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->g = (unsigned char) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

unsigned int v2;
if (JS_ToUint32(ctx, &v2, argv[2]))
        goto fail;
s->b = (unsigned char) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

unsigned int v3;
if (JS_ToUint32(ctx, &v3, argv[3]))
        goto fail;
s->a = (unsigned char) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Color_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Color_class = {
    "Color",
    .finalizer = js_Color_finalizer,
};

static const JSCFunctionListEntry js_Color_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("r", js_Color_get, js_Color_set, 0),
    JS_CGETSET_MAGIC_DEF("g", js_Color_get, js_Color_set, 1),
    JS_CGETSET_MAGIC_DEF("b", js_Color_get, js_Color_set, 2),
    JS_CGETSET_MAGIC_DEF("a", js_Color_get, js_Color_set, 3),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Color", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Color(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Color_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Color_class_id, &js_Color_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Color_proto_funcs, countof(js_Color_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Color_ctor, "Color", 4, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Color_class_id, proto);

    JS_SetModuleExport(ctx, m, "Color", class);
    return 0;
}



static JSClassID js_Rectangle_class_id;

static JSValue js_Rectangle_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Rectangle *s = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewFloat64(ctx, (double) s->x);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->y);
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->width);
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->height);
}


    return JS_UNDEFINED;
}

static JSValue js_Rectangle_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Rectangle *s = JS_GetOpaque2(ctx, this_val, js_Rectangle_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    double v0;
    if (JS_ToFloat64(ctx, &v0, val))
        return JS_EXCEPTION;
    s->x = (float) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->y = (float) v1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->width = (float) v2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->height = (float) v3;
}

    
    return JS_UNDEFINED;
}

static void js_Rectangle_finalizer(JSRuntime *rt, JSValue val)
{
    Rectangle *s = JS_GetOpaque(val, js_Rectangle_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Rectangle_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Rectangle_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Rectangle *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
double v0;
if (JS_ToFloat64(ctx, &v0, argv[0]))
        goto fail;
s->x = (float) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->y = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->width = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->height = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Rectangle_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Rectangle_class = {
    "Rectangle",
    .finalizer = js_Rectangle_finalizer,
};

static const JSCFunctionListEntry js_Rectangle_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("x", js_Rectangle_get, js_Rectangle_set, 0),
    JS_CGETSET_MAGIC_DEF("y", js_Rectangle_get, js_Rectangle_set, 1),
    JS_CGETSET_MAGIC_DEF("width", js_Rectangle_get, js_Rectangle_set, 2),
    JS_CGETSET_MAGIC_DEF("height", js_Rectangle_get, js_Rectangle_set, 3),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Rectangle", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Rectangle(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Rectangle_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Rectangle_class_id, &js_Rectangle_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Rectangle_proto_funcs, countof(js_Rectangle_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Rectangle_ctor, "Rectangle", 4, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Rectangle_class_id, proto);

    JS_SetModuleExport(ctx, m, "Rectangle", class);
    return 0;
}



static JSClassID js_Image_class_id;

static JSValue js_Image_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Image *s = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->data);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->width);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->height);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->mipmaps);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->format);
}


    return JS_UNDEFINED;
}

static JSValue js_Image_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Image *s = JS_GetOpaque2(ctx, this_val, js_Image_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->data = (void *) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->width = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->height = (int) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->mipmaps = (int) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->format = (int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Image_finalizer(JSRuntime *rt, JSValue val)
{
    Image *s = JS_GetOpaque(val, js_Image_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Image_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Image_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Image *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->data = (void *) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->width = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->height = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->mipmaps = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->format = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Image_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Image_class = {
    "Image",
    .finalizer = js_Image_finalizer,
};

static const JSCFunctionListEntry js_Image_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("data", js_Image_get, js_Image_set, 0),
    JS_CGETSET_MAGIC_DEF("width", js_Image_get, js_Image_set, 1),
    JS_CGETSET_MAGIC_DEF("height", js_Image_get, js_Image_set, 2),
    JS_CGETSET_MAGIC_DEF("mipmaps", js_Image_get, js_Image_set, 3),
    JS_CGETSET_MAGIC_DEF("format", js_Image_get, js_Image_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Image", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Image(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Image_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Image_class_id, &js_Image_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Image_proto_funcs, countof(js_Image_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Image_ctor, "Image", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Image_class_id, proto);

    JS_SetModuleExport(ctx, m, "Image", class);
    return 0;
}



static JSClassID js_Texture_class_id;

static JSValue js_Texture_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Texture *s = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->id);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->width);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->height);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->mipmaps);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->format);
}


    return JS_UNDEFINED;
}

static JSValue js_Texture_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Texture *s = JS_GetOpaque2(ctx, this_val, js_Texture_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->id = (unsigned int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->width = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->height = (int) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->mipmaps = (int) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->format = (int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Texture_finalizer(JSRuntime *rt, JSValue val)
{
    Texture *s = JS_GetOpaque(val, js_Texture_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Texture_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Texture_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Texture *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->id = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->width = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->height = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->mipmaps = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->format = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Texture_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Texture_class = {
    "Texture",
    .finalizer = js_Texture_finalizer,
};

static const JSCFunctionListEntry js_Texture_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("id", js_Texture_get, js_Texture_set, 0),
    JS_CGETSET_MAGIC_DEF("width", js_Texture_get, js_Texture_set, 1),
    JS_CGETSET_MAGIC_DEF("height", js_Texture_get, js_Texture_set, 2),
    JS_CGETSET_MAGIC_DEF("mipmaps", js_Texture_get, js_Texture_set, 3),
    JS_CGETSET_MAGIC_DEF("format", js_Texture_get, js_Texture_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Texture", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Texture(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Texture_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Texture_class_id, &js_Texture_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Texture_proto_funcs, countof(js_Texture_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Texture_ctor, "Texture", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Texture_class_id, proto);

    JS_SetModuleExport(ctx, m, "Texture", class);
    return 0;
}



static JSClassID js_Texture2D_class_id;

static JSValue js_Texture2D_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Texture2D *s = JS_GetOpaque2(ctx, this_val, js_Texture2D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->id);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->width);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->height);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->mipmaps);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->format);
}


    return JS_UNDEFINED;
}

static JSValue js_Texture2D_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Texture2D *s = JS_GetOpaque2(ctx, this_val, js_Texture2D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->id = (unsigned int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->width = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->height = (int) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->mipmaps = (int) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->format = (int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Texture2D_finalizer(JSRuntime *rt, JSValue val)
{
    Texture2D *s = JS_GetOpaque(val, js_Texture2D_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Texture2D_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Texture2D_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Texture2D *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->id = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->width = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->height = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->mipmaps = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->format = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Texture2D_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Texture2D_class = {
    "Texture2D",
    .finalizer = js_Texture2D_finalizer,
};

static const JSCFunctionListEntry js_Texture2D_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("id", js_Texture2D_get, js_Texture2D_set, 0),
    JS_CGETSET_MAGIC_DEF("width", js_Texture2D_get, js_Texture2D_set, 1),
    JS_CGETSET_MAGIC_DEF("height", js_Texture2D_get, js_Texture2D_set, 2),
    JS_CGETSET_MAGIC_DEF("mipmaps", js_Texture2D_get, js_Texture2D_set, 3),
    JS_CGETSET_MAGIC_DEF("format", js_Texture2D_get, js_Texture2D_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Texture2D", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Texture2D(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Texture2D_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Texture2D_class_id, &js_Texture2D_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Texture2D_proto_funcs, countof(js_Texture2D_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Texture2D_ctor, "Texture2D", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Texture2D_class_id, proto);

    JS_SetModuleExport(ctx, m, "Texture2D", class);
    return 0;
}



static JSClassID js_TextureCubemap_class_id;

static JSValue js_TextureCubemap_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    TextureCubemap *s = JS_GetOpaque2(ctx, this_val, js_TextureCubemap_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->id);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->width);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->height);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->mipmaps);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->format);
}


    return JS_UNDEFINED;
}

static JSValue js_TextureCubemap_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    TextureCubemap *s = JS_GetOpaque2(ctx, this_val, js_TextureCubemap_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->id = (unsigned int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->width = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->height = (int) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->mipmaps = (int) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->format = (int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_TextureCubemap_finalizer(JSRuntime *rt, JSValue val)
{
    TextureCubemap *s = JS_GetOpaque(val, js_TextureCubemap_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_TextureCubemap_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_TextureCubemap_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    TextureCubemap *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->id = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->width = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->height = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->mipmaps = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->format = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_TextureCubemap_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_TextureCubemap_class = {
    "TextureCubemap",
    .finalizer = js_TextureCubemap_finalizer,
};

static const JSCFunctionListEntry js_TextureCubemap_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("id", js_TextureCubemap_get, js_TextureCubemap_set, 0),
    JS_CGETSET_MAGIC_DEF("width", js_TextureCubemap_get, js_TextureCubemap_set, 1),
    JS_CGETSET_MAGIC_DEF("height", js_TextureCubemap_get, js_TextureCubemap_set, 2),
    JS_CGETSET_MAGIC_DEF("mipmaps", js_TextureCubemap_get, js_TextureCubemap_set, 3),
    JS_CGETSET_MAGIC_DEF("format", js_TextureCubemap_get, js_TextureCubemap_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "TextureCubemap", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_TextureCubemap(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_TextureCubemap_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_TextureCubemap_class_id, &js_TextureCubemap_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_TextureCubemap_proto_funcs, countof(js_TextureCubemap_proto_funcs));

    class = JS_NewCFunction2(ctx, js_TextureCubemap_ctor, "TextureCubemap", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_TextureCubemap_class_id, proto);

    JS_SetModuleExport(ctx, m, "TextureCubemap", class);
    return 0;
}



static JSClassID js_RenderTexture_class_id;

static JSValue js_RenderTexture_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    RenderTexture *s = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->id);
}

if (magic == 1) {
    Texture* ret_ptr = (Texture *)js_malloc(ctx, sizeof(Texture));
    *ret_ptr = s->texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    Texture* ret_ptr = (Texture *)js_malloc(ctx, sizeof(Texture));
    *ret_ptr = s->depth;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_RenderTexture_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    RenderTexture *s = JS_GetOpaque2(ctx, this_val, js_RenderTexture_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->id = (unsigned int) v0;
}

if (magic == 1) {
    Texture * argptr1 = (Texture *)JS_GetOpaque2(ctx, val, js_Texture_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr1;
}

if (magic == 2) {
    Texture * argptr2 = (Texture *)JS_GetOpaque2(ctx, val, js_Texture_class_id);
    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->depth = *argptr2;
}

    
    return JS_UNDEFINED;
}

static void js_RenderTexture_finalizer(JSRuntime *rt, JSValue val)
{
    RenderTexture *s = JS_GetOpaque(val, js_RenderTexture_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_RenderTexture_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_RenderTexture_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    RenderTexture *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->id = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

    Texture * argptr1 = (Texture *)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr1;

    Texture * argptr2 = (Texture *)JS_GetOpaque2(ctx, argv[2], js_Texture_class_id);
                    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->depth = *argptr2;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_RenderTexture_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_RenderTexture_class = {
    "RenderTexture",
    .finalizer = js_RenderTexture_finalizer,
};

static const JSCFunctionListEntry js_RenderTexture_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("id", js_RenderTexture_get, js_RenderTexture_set, 0),
    JS_CGETSET_MAGIC_DEF("texture", js_RenderTexture_get, js_RenderTexture_set, 1),
    JS_CGETSET_MAGIC_DEF("depth", js_RenderTexture_get, js_RenderTexture_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "RenderTexture", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_RenderTexture(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_RenderTexture_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_RenderTexture_class_id, &js_RenderTexture_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_RenderTexture_proto_funcs, countof(js_RenderTexture_proto_funcs));

    class = JS_NewCFunction2(ctx, js_RenderTexture_ctor, "RenderTexture", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_RenderTexture_class_id, proto);

    JS_SetModuleExport(ctx, m, "RenderTexture", class);
    return 0;
}



static JSClassID js_RenderTexture2D_class_id;

static JSValue js_RenderTexture2D_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    RenderTexture2D *s = JS_GetOpaque2(ctx, this_val, js_RenderTexture2D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->id);
}

if (magic == 1) {
    Texture* ret_ptr = (Texture *)js_malloc(ctx, sizeof(Texture));
    *ret_ptr = s->texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    Texture* ret_ptr = (Texture *)js_malloc(ctx, sizeof(Texture));
    *ret_ptr = s->depth;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_RenderTexture2D_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    RenderTexture2D *s = JS_GetOpaque2(ctx, this_val, js_RenderTexture2D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->id = (unsigned int) v0;
}

if (magic == 1) {
    Texture * argptr1 = (Texture *)JS_GetOpaque2(ctx, val, js_Texture_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr1;
}

if (magic == 2) {
    Texture * argptr2 = (Texture *)JS_GetOpaque2(ctx, val, js_Texture_class_id);
    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->depth = *argptr2;
}

    
    return JS_UNDEFINED;
}

static void js_RenderTexture2D_finalizer(JSRuntime *rt, JSValue val)
{
    RenderTexture2D *s = JS_GetOpaque(val, js_RenderTexture2D_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_RenderTexture2D_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_RenderTexture2D_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    RenderTexture2D *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->id = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

    Texture * argptr1 = (Texture *)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr1;

    Texture * argptr2 = (Texture *)JS_GetOpaque2(ctx, argv[2], js_Texture_class_id);
                    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->depth = *argptr2;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_RenderTexture2D_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_RenderTexture2D_class = {
    "RenderTexture2D",
    .finalizer = js_RenderTexture2D_finalizer,
};

static const JSCFunctionListEntry js_RenderTexture2D_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("id", js_RenderTexture2D_get, js_RenderTexture2D_set, 0),
    JS_CGETSET_MAGIC_DEF("texture", js_RenderTexture2D_get, js_RenderTexture2D_set, 1),
    JS_CGETSET_MAGIC_DEF("depth", js_RenderTexture2D_get, js_RenderTexture2D_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "RenderTexture2D", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_RenderTexture2D(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_RenderTexture2D_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_RenderTexture2D_class_id, &js_RenderTexture2D_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_RenderTexture2D_proto_funcs, countof(js_RenderTexture2D_proto_funcs));

    class = JS_NewCFunction2(ctx, js_RenderTexture2D_ctor, "RenderTexture2D", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_RenderTexture2D_class_id, proto);

    JS_SetModuleExport(ctx, m, "RenderTexture2D", class);
    return 0;
}



static JSClassID js_NPatchInfo_class_id;

static JSValue js_NPatchInfo_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    NPatchInfo *s = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Rectangle* ret_ptr = (Rectangle *)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = s->source;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->left);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->top);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->right);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->bottom);
}

if (magic == 5) {
    return JS_NewInt32(ctx, (int) s->layout);
}


    return JS_UNDEFINED;
}

static JSValue js_NPatchInfo_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    NPatchInfo *s = JS_GetOpaque2(ctx, this_val, js_NPatchInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, val, js_Rectangle_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->source = *argptr0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->left = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->top = (int) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->right = (int) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->bottom = (int) v4;
}

if (magic == 5) {
    int v5;
    if (JS_ToInt32(ctx, &v5, val))
        return JS_EXCEPTION;
    s->layout = (int) v5;
}

    
    return JS_UNDEFINED;
}

static void js_NPatchInfo_finalizer(JSRuntime *rt, JSValue val)
{
    NPatchInfo *s = JS_GetOpaque(val, js_NPatchInfo_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_NPatchInfo_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_NPatchInfo_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    NPatchInfo *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->source = *argptr0;

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->left = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->top = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->right = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->bottom = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

int v5;
if (JS_ToInt32(ctx, &v5, argv[5]))
        goto fail;
s->layout = (int) v5;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 5 = %lf", s->5);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_NPatchInfo_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_NPatchInfo_class = {
    "NPatchInfo",
    .finalizer = js_NPatchInfo_finalizer,
};

static const JSCFunctionListEntry js_NPatchInfo_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("source", js_NPatchInfo_get, js_NPatchInfo_set, 0),
    JS_CGETSET_MAGIC_DEF("left", js_NPatchInfo_get, js_NPatchInfo_set, 1),
    JS_CGETSET_MAGIC_DEF("top", js_NPatchInfo_get, js_NPatchInfo_set, 2),
    JS_CGETSET_MAGIC_DEF("right", js_NPatchInfo_get, js_NPatchInfo_set, 3),
    JS_CGETSET_MAGIC_DEF("bottom", js_NPatchInfo_get, js_NPatchInfo_set, 4),
    JS_CGETSET_MAGIC_DEF("layout", js_NPatchInfo_get, js_NPatchInfo_set, 5),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "NPatchInfo", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_NPatchInfo(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_NPatchInfo_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_NPatchInfo_class_id, &js_NPatchInfo_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_NPatchInfo_proto_funcs, countof(js_NPatchInfo_proto_funcs));

    class = JS_NewCFunction2(ctx, js_NPatchInfo_ctor, "NPatchInfo", 6, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_NPatchInfo_class_id, proto);

    JS_SetModuleExport(ctx, m, "NPatchInfo", class);
    return 0;
}



static JSClassID js_GlyphInfo_class_id;

static JSValue js_GlyphInfo_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    GlyphInfo *s = JS_GetOpaque2(ctx, this_val, js_GlyphInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewInt32(ctx, (int) s->value);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->offsetX);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->offsetY);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->advanceX);
}

if (magic == 4) {
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = s->image;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_GlyphInfo_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    GlyphInfo *s = JS_GetOpaque2(ctx, this_val, js_GlyphInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    int v0;
    if (JS_ToInt32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->value = (int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->offsetX = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->offsetY = (int) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->advanceX = (int) v3;
}

if (magic == 4) {
    Image * argptr4 = (Image *)JS_GetOpaque2(ctx, val, js_Image_class_id);
    
    if (argptr4 == NULL) return JS_EXCEPTION;
                    
    s->image = *argptr4;
}

    
    return JS_UNDEFINED;
}

static void js_GlyphInfo_finalizer(JSRuntime *rt, JSValue val)
{
    GlyphInfo *s = JS_GetOpaque(val, js_GlyphInfo_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_GlyphInfo_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_GlyphInfo_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    GlyphInfo *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
int v0;
if (JS_ToInt32(ctx, &v0, argv[0]))
        goto fail;
s->value = (int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->offsetX = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->offsetY = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->advanceX = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

    Image * argptr4 = (Image *)JS_GetOpaque2(ctx, argv[4], js_Image_class_id);
                    
    if (argptr4 == NULL) return JS_EXCEPTION;
                    
    s->image = *argptr4;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_GlyphInfo_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_GlyphInfo_class = {
    "GlyphInfo",
    .finalizer = js_GlyphInfo_finalizer,
};

static const JSCFunctionListEntry js_GlyphInfo_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("value", js_GlyphInfo_get, js_GlyphInfo_set, 0),
    JS_CGETSET_MAGIC_DEF("offsetX", js_GlyphInfo_get, js_GlyphInfo_set, 1),
    JS_CGETSET_MAGIC_DEF("offsetY", js_GlyphInfo_get, js_GlyphInfo_set, 2),
    JS_CGETSET_MAGIC_DEF("advanceX", js_GlyphInfo_get, js_GlyphInfo_set, 3),
    JS_CGETSET_MAGIC_DEF("image", js_GlyphInfo_get, js_GlyphInfo_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GlyphInfo", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_GlyphInfo(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_GlyphInfo_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_GlyphInfo_class_id, &js_GlyphInfo_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_GlyphInfo_proto_funcs, countof(js_GlyphInfo_proto_funcs));

    class = JS_NewCFunction2(ctx, js_GlyphInfo_ctor, "GlyphInfo", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_GlyphInfo_class_id, proto);

    JS_SetModuleExport(ctx, m, "GlyphInfo", class);
    return 0;
}



static JSClassID js_Font_class_id;

static JSValue js_Font_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Font *s = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewInt32(ctx, (int) s->baseSize);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->glyphCount);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->glyphPadding);
}

if (magic == 3) {
    Texture2D* ret_ptr = (Texture2D *)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = s->texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture2D_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

            
            

    return JS_UNDEFINED;
}

static JSValue js_Font_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Font *s = JS_GetOpaque2(ctx, this_val, js_Font_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    int v0;
    if (JS_ToInt32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->baseSize = (int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->glyphCount = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->glyphPadding = (int) v2;
}

if (magic == 3) {
    Texture2D * argptr3 = (Texture2D *)JS_GetOpaque2(ctx, val, js_Texture2D_class_id);
    
    if (argptr3 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr3;
}

            
            
    
    return JS_UNDEFINED;
}

static void js_Font_finalizer(JSRuntime *rt, JSValue val)
{
    Font *s = JS_GetOpaque(val, js_Font_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Font_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Font_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Font *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
int v0;
if (JS_ToInt32(ctx, &v0, argv[0]))
        goto fail;
s->baseSize = (int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->glyphCount = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->glyphPadding = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

    Texture2D * argptr3 = (Texture2D *)JS_GetOpaque2(ctx, argv[3], js_Texture2D_class_id);
                    
    if (argptr3 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr3;

            
            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Font_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Font_class = {
    "Font",
    .finalizer = js_Font_finalizer,
};

static const JSCFunctionListEntry js_Font_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("baseSize", js_Font_get, js_Font_set, 0),
    JS_CGETSET_MAGIC_DEF("glyphCount", js_Font_get, js_Font_set, 1),
    JS_CGETSET_MAGIC_DEF("glyphPadding", js_Font_get, js_Font_set, 2),
    JS_CGETSET_MAGIC_DEF("texture", js_Font_get, js_Font_set, 3),
    JS_CGETSET_MAGIC_DEF("recs", js_Font_get, js_Font_set, 4),
    JS_CGETSET_MAGIC_DEF("glyphs", js_Font_get, js_Font_set, 5),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Font", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Font(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Font_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Font_class_id, &js_Font_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Font_proto_funcs, countof(js_Font_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Font_ctor, "Font", 6, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Font_class_id, proto);

    JS_SetModuleExport(ctx, m, "Font", class);
    return 0;
}



static JSClassID js_Camera3D_class_id;

static JSValue js_Camera3D_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Camera3D *s = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->up;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->fovy);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->projection);
}


    return JS_UNDEFINED;
}

static JSValue js_Camera3D_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Camera3D *s = JS_GetOpaque2(ctx, this_val, js_Camera3D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->position = *argptr0;
}

if (magic == 1) {
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->target = *argptr1;
}

if (magic == 2) {
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->up = *argptr2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->fovy = (float) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->projection = (int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Camera3D_finalizer(JSRuntime *rt, JSValue val)
{
    Camera3D *s = JS_GetOpaque(val, js_Camera3D_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Camera3D_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Camera3D_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Camera3D *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->position = *argptr0;

    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->target = *argptr1;

    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
                    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->up = *argptr2;

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->fovy = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->projection = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Camera3D_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Camera3D_class = {
    "Camera3D",
    .finalizer = js_Camera3D_finalizer,
};

static const JSCFunctionListEntry js_Camera3D_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("position", js_Camera3D_get, js_Camera3D_set, 0),
    JS_CGETSET_MAGIC_DEF("target", js_Camera3D_get, js_Camera3D_set, 1),
    JS_CGETSET_MAGIC_DEF("up", js_Camera3D_get, js_Camera3D_set, 2),
    JS_CGETSET_MAGIC_DEF("fovy", js_Camera3D_get, js_Camera3D_set, 3),
    JS_CGETSET_MAGIC_DEF("projection", js_Camera3D_get, js_Camera3D_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Camera3D", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Camera3D(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Camera3D_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Camera3D_class_id, &js_Camera3D_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Camera3D_proto_funcs, countof(js_Camera3D_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Camera3D_ctor, "Camera3D", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Camera3D_class_id, proto);

    JS_SetModuleExport(ctx, m, "Camera3D", class);
    return 0;
}



static JSClassID js_Camera_class_id;

static JSValue js_Camera_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Camera *s = JS_GetOpaque2(ctx, this_val, js_Camera_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->up;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->fovy);
}

if (magic == 4) {
    return JS_NewInt32(ctx, (int) s->projection);
}


    return JS_UNDEFINED;
}

static JSValue js_Camera_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Camera *s = JS_GetOpaque2(ctx, this_val, js_Camera_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->position = *argptr0;
}

if (magic == 1) {
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->target = *argptr1;
}

if (magic == 2) {
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->up = *argptr2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->fovy = (float) v3;
}

if (magic == 4) {
    int v4;
    if (JS_ToInt32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->projection = (int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Camera_finalizer(JSRuntime *rt, JSValue val)
{
    Camera *s = JS_GetOpaque(val, js_Camera_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Camera_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Camera_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Camera *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->position = *argptr0;

    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->target = *argptr1;

    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
                    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->up = *argptr2;

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->fovy = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

int v4;
if (JS_ToInt32(ctx, &v4, argv[4]))
        goto fail;
s->projection = (int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Camera_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Camera_class = {
    "Camera",
    .finalizer = js_Camera_finalizer,
};

static const JSCFunctionListEntry js_Camera_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("position", js_Camera_get, js_Camera_set, 0),
    JS_CGETSET_MAGIC_DEF("target", js_Camera_get, js_Camera_set, 1),
    JS_CGETSET_MAGIC_DEF("up", js_Camera_get, js_Camera_set, 2),
    JS_CGETSET_MAGIC_DEF("fovy", js_Camera_get, js_Camera_set, 3),
    JS_CGETSET_MAGIC_DEF("projection", js_Camera_get, js_Camera_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Camera", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Camera(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Camera_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Camera_class_id, &js_Camera_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Camera_proto_funcs, countof(js_Camera_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Camera_ctor, "Camera", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Camera_class_id, proto);

    JS_SetModuleExport(ctx, m, "Camera", class);
    return 0;
}



static JSClassID js_Camera2D_class_id;

static JSValue js_Camera2D_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Camera2D *s = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = s->offset;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = s->target;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->rotation);
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->zoom);
}


    return JS_UNDEFINED;
}

static JSValue js_Camera2D_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Camera2D *s = JS_GetOpaque2(ctx, this_val, js_Camera2D_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, val, js_Vector2_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->offset = *argptr0;
}

if (magic == 1) {
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, val, js_Vector2_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->target = *argptr1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->rotation = (float) v2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->zoom = (float) v3;
}

    
    return JS_UNDEFINED;
}

static void js_Camera2D_finalizer(JSRuntime *rt, JSValue val)
{
    Camera2D *s = JS_GetOpaque(val, js_Camera2D_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Camera2D_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Camera2D_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Camera2D *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->offset = *argptr0;

    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->target = *argptr1;

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->rotation = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->zoom = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Camera2D_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Camera2D_class = {
    "Camera2D",
    .finalizer = js_Camera2D_finalizer,
};

static const JSCFunctionListEntry js_Camera2D_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("offset", js_Camera2D_get, js_Camera2D_set, 0),
    JS_CGETSET_MAGIC_DEF("target", js_Camera2D_get, js_Camera2D_set, 1),
    JS_CGETSET_MAGIC_DEF("rotation", js_Camera2D_get, js_Camera2D_set, 2),
    JS_CGETSET_MAGIC_DEF("zoom", js_Camera2D_get, js_Camera2D_set, 3),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Camera2D", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Camera2D(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Camera2D_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Camera2D_class_id, &js_Camera2D_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Camera2D_proto_funcs, countof(js_Camera2D_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Camera2D_ctor, "Camera2D", 4, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Camera2D_class_id, proto);

    JS_SetModuleExport(ctx, m, "Camera2D", class);
    return 0;
}



static JSClassID js_Mesh_class_id;

static JSValue js_Mesh_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Mesh *s = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewInt32(ctx, (int) s->vertexCount);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->triangleCount);
}

            
            
            
            
            
            
            
            
            
            
            
if (magic == 13) {
    return JS_NewUint32(ctx, (unsigned int) s->vaoId);
}

            

    return JS_UNDEFINED;
}

static JSValue js_Mesh_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Mesh *s = JS_GetOpaque2(ctx, this_val, js_Mesh_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    int v0;
    if (JS_ToInt32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->vertexCount = (int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->triangleCount = (int) v1;
}

            
            
            
            
            
            
            
            
            
            
            
if (magic == 13) {
    unsigned int v13;
    if (JS_ToUint32(ctx, &v13, val))
        return JS_EXCEPTION;
    s->vaoId = (unsigned int) v13;
}

            
    
    return JS_UNDEFINED;
}

static void js_Mesh_finalizer(JSRuntime *rt, JSValue val)
{
    Mesh *s = JS_GetOpaque(val, js_Mesh_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Mesh_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Mesh_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Mesh *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
int v0;
if (JS_ToInt32(ctx, &v0, argv[0]))
        goto fail;
s->vertexCount = (int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->triangleCount = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

            
            
            
            
            
            
            
            
            
            
            
unsigned int v13;
if (JS_ToUint32(ctx, &v13, argv[13]))
        goto fail;
s->vaoId = (unsigned int) v13;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 13 = %lf", s->13);*/
        

            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Mesh_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Mesh_class = {
    "Mesh",
    .finalizer = js_Mesh_finalizer,
};

static const JSCFunctionListEntry js_Mesh_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("vertexCount", js_Mesh_get, js_Mesh_set, 0),
    JS_CGETSET_MAGIC_DEF("triangleCount", js_Mesh_get, js_Mesh_set, 1),
    JS_CGETSET_MAGIC_DEF("vertices", js_Mesh_get, js_Mesh_set, 2),
    JS_CGETSET_MAGIC_DEF("texcoords", js_Mesh_get, js_Mesh_set, 3),
    JS_CGETSET_MAGIC_DEF("texcoords2", js_Mesh_get, js_Mesh_set, 4),
    JS_CGETSET_MAGIC_DEF("normals", js_Mesh_get, js_Mesh_set, 5),
    JS_CGETSET_MAGIC_DEF("tangents", js_Mesh_get, js_Mesh_set, 6),
    JS_CGETSET_MAGIC_DEF("colors", js_Mesh_get, js_Mesh_set, 7),
    JS_CGETSET_MAGIC_DEF("indices", js_Mesh_get, js_Mesh_set, 8),
    JS_CGETSET_MAGIC_DEF("animVertices", js_Mesh_get, js_Mesh_set, 9),
    JS_CGETSET_MAGIC_DEF("animNormals", js_Mesh_get, js_Mesh_set, 10),
    JS_CGETSET_MAGIC_DEF("boneIds", js_Mesh_get, js_Mesh_set, 11),
    JS_CGETSET_MAGIC_DEF("boneWeights", js_Mesh_get, js_Mesh_set, 12),
    JS_CGETSET_MAGIC_DEF("vaoId", js_Mesh_get, js_Mesh_set, 13),
    JS_CGETSET_MAGIC_DEF("vboId", js_Mesh_get, js_Mesh_set, 14),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Mesh", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Mesh(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Mesh_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Mesh_class_id, &js_Mesh_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Mesh_proto_funcs, countof(js_Mesh_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Mesh_ctor, "Mesh", 15, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Mesh_class_id, proto);

    JS_SetModuleExport(ctx, m, "Mesh", class);
    return 0;
}



static JSClassID js_Shader_class_id;

static JSValue js_Shader_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Shader *s = JS_GetOpaque2(ctx, this_val, js_Shader_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->id);
}

            

    return JS_UNDEFINED;
}

static JSValue js_Shader_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Shader *s = JS_GetOpaque2(ctx, this_val, js_Shader_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->id = (unsigned int) v0;
}

            
    
    return JS_UNDEFINED;
}

static void js_Shader_finalizer(JSRuntime *rt, JSValue val)
{
    Shader *s = JS_GetOpaque(val, js_Shader_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Shader_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Shader_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Shader *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->id = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Shader_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Shader_class = {
    "Shader",
    .finalizer = js_Shader_finalizer,
};

static const JSCFunctionListEntry js_Shader_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("id", js_Shader_get, js_Shader_set, 0),
    JS_CGETSET_MAGIC_DEF("locs", js_Shader_get, js_Shader_set, 1),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Shader", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Shader(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Shader_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Shader_class_id, &js_Shader_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Shader_proto_funcs, countof(js_Shader_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Shader_ctor, "Shader", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Shader_class_id, proto);

    JS_SetModuleExport(ctx, m, "Shader", class);
    return 0;
}



static JSClassID js_MaterialMap_class_id;

static JSValue js_MaterialMap_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    MaterialMap *s = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Texture2D* ret_ptr = (Texture2D *)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = s->texture;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture2D_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = s->color;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->value);
}


    return JS_UNDEFINED;
}

static JSValue js_MaterialMap_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    MaterialMap *s = JS_GetOpaque2(ctx, this_val, js_MaterialMap_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, val, js_Texture2D_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr0;
}

if (magic == 1) {
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, val, js_Color_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->color = *argptr1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->value = (float) v2;
}

    
    return JS_UNDEFINED;
}

static void js_MaterialMap_finalizer(JSRuntime *rt, JSValue val)
{
    MaterialMap *s = JS_GetOpaque(val, js_MaterialMap_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_MaterialMap_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_MaterialMap_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    MaterialMap *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->texture = *argptr0;

    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->color = *argptr1;

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->value = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_MaterialMap_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_MaterialMap_class = {
    "MaterialMap",
    .finalizer = js_MaterialMap_finalizer,
};

static const JSCFunctionListEntry js_MaterialMap_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("texture", js_MaterialMap_get, js_MaterialMap_set, 0),
    JS_CGETSET_MAGIC_DEF("color", js_MaterialMap_get, js_MaterialMap_set, 1),
    JS_CGETSET_MAGIC_DEF("value", js_MaterialMap_get, js_MaterialMap_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "MaterialMap", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_MaterialMap(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_MaterialMap_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_MaterialMap_class_id, &js_MaterialMap_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_MaterialMap_proto_funcs, countof(js_MaterialMap_proto_funcs));

    class = JS_NewCFunction2(ctx, js_MaterialMap_ctor, "MaterialMap", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_MaterialMap_class_id, proto);

    JS_SetModuleExport(ctx, m, "MaterialMap", class);
    return 0;
}



static JSClassID js_Material_class_id;

static JSValue js_Material_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Material *s = JS_GetOpaque2(ctx, this_val, js_Material_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Shader* ret_ptr = (Shader *)js_malloc(ctx, sizeof(Shader));
    *ret_ptr = s->shader;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

            
            

    return JS_UNDEFINED;
}

static JSValue js_Material_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Material *s = JS_GetOpaque2(ctx, this_val, js_Material_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, val, js_Shader_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->shader = *argptr0;
}

            
            
    
    return JS_UNDEFINED;
}

static void js_Material_finalizer(JSRuntime *rt, JSValue val)
{
    Material *s = JS_GetOpaque(val, js_Material_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Material_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Material_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Material *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->shader = *argptr0;

            
            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Material_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Material_class = {
    "Material",
    .finalizer = js_Material_finalizer,
};

static const JSCFunctionListEntry js_Material_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("shader", js_Material_get, js_Material_set, 0),
    JS_CGETSET_MAGIC_DEF("maps", js_Material_get, js_Material_set, 1),
    JS_CGETSET_MAGIC_DEF("params", js_Material_get, js_Material_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Material", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Material(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Material_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Material_class_id, &js_Material_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Material_proto_funcs, countof(js_Material_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Material_ctor, "Material", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Material_class_id, proto);

    JS_SetModuleExport(ctx, m, "Material", class);
    return 0;
}



static JSClassID js_Transform_class_id;

static JSValue js_Transform_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Transform *s = JS_GetOpaque2(ctx, this_val, js_Transform_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->translation;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Quaternion* ret_ptr = (Quaternion *)js_malloc(ctx, sizeof(Quaternion));
    *ret_ptr = s->rotation;
    JSValue ret = JS_NewObjectClass(ctx, js_Quaternion_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 2) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->scale;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_Transform_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Transform *s = JS_GetOpaque2(ctx, this_val, js_Transform_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->translation = *argptr0;
}

if (magic == 1) {
    Quaternion * argptr1 = (Quaternion *)JS_GetOpaque2(ctx, val, js_Quaternion_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->rotation = *argptr1;
}

if (magic == 2) {
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->scale = *argptr2;
}

    
    return JS_UNDEFINED;
}

static void js_Transform_finalizer(JSRuntime *rt, JSValue val)
{
    Transform *s = JS_GetOpaque(val, js_Transform_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Transform_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Transform_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Transform *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->translation = *argptr0;

    Quaternion * argptr1 = (Quaternion *)JS_GetOpaque2(ctx, argv[1], js_Quaternion_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->rotation = *argptr1;

    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
                    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->scale = *argptr2;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Transform_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Transform_class = {
    "Transform",
    .finalizer = js_Transform_finalizer,
};

static const JSCFunctionListEntry js_Transform_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("translation", js_Transform_get, js_Transform_set, 0),
    JS_CGETSET_MAGIC_DEF("rotation", js_Transform_get, js_Transform_set, 1),
    JS_CGETSET_MAGIC_DEF("scale", js_Transform_get, js_Transform_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Transform", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Transform(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Transform_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Transform_class_id, &js_Transform_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Transform_proto_funcs, countof(js_Transform_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Transform_ctor, "Transform", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Transform_class_id, proto);

    JS_SetModuleExport(ctx, m, "Transform", class);
    return 0;
}



static JSClassID js_BoneInfo_class_id;

static JSValue js_BoneInfo_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    BoneInfo *s = JS_GetOpaque2(ctx, this_val, js_BoneInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
            
if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->parent);
}


    return JS_UNDEFINED;
}

static JSValue js_BoneInfo_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    BoneInfo *s = JS_GetOpaque2(ctx, this_val, js_BoneInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
            
if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->parent = (int) v1;
}

    
    return JS_UNDEFINED;
}

static void js_BoneInfo_finalizer(JSRuntime *rt, JSValue val)
{
    BoneInfo *s = JS_GetOpaque(val, js_BoneInfo_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_BoneInfo_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_BoneInfo_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    BoneInfo *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
            
int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->parent = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_BoneInfo_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_BoneInfo_class = {
    "BoneInfo",
    .finalizer = js_BoneInfo_finalizer,
};

static const JSCFunctionListEntry js_BoneInfo_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("name", js_BoneInfo_get, js_BoneInfo_set, 0),
    JS_CGETSET_MAGIC_DEF("parent", js_BoneInfo_get, js_BoneInfo_set, 1),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "BoneInfo", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_BoneInfo(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_BoneInfo_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_BoneInfo_class_id, &js_BoneInfo_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_BoneInfo_proto_funcs, countof(js_BoneInfo_proto_funcs));

    class = JS_NewCFunction2(ctx, js_BoneInfo_ctor, "BoneInfo", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_BoneInfo_class_id, proto);

    JS_SetModuleExport(ctx, m, "BoneInfo", class);
    return 0;
}



static JSClassID js_Model_class_id;

static JSValue js_Model_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Model *s = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Matrix* ret_ptr = (Matrix *)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = s->transform;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->meshCount);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->materialCount);
}

            
            
            
if (magic == 6) {
    return JS_NewInt32(ctx, (int) s->boneCount);
}

            
            

    return JS_UNDEFINED;
}

static JSValue js_Model_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Model *s = JS_GetOpaque2(ctx, this_val, js_Model_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Matrix * argptr0 = (Matrix *)JS_GetOpaque2(ctx, val, js_Matrix_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->transform = *argptr0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->meshCount = (int) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->materialCount = (int) v2;
}

            
            
            
if (magic == 6) {
    int v6;
    if (JS_ToInt32(ctx, &v6, val))
        return JS_EXCEPTION;
    s->boneCount = (int) v6;
}

            
            
    
    return JS_UNDEFINED;
}

static void js_Model_finalizer(JSRuntime *rt, JSValue val)
{
    Model *s = JS_GetOpaque(val, js_Model_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Model_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Model_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Model *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Matrix * argptr0 = (Matrix *)JS_GetOpaque2(ctx, argv[0], js_Matrix_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->transform = *argptr0;

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->meshCount = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->materialCount = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

            
            
            
int v6;
if (JS_ToInt32(ctx, &v6, argv[6]))
        goto fail;
s->boneCount = (int) v6;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 6 = %lf", s->6);*/
        

            
            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Model_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Model_class = {
    "Model",
    .finalizer = js_Model_finalizer,
};

static const JSCFunctionListEntry js_Model_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("transform", js_Model_get, js_Model_set, 0),
    JS_CGETSET_MAGIC_DEF("meshCount", js_Model_get, js_Model_set, 1),
    JS_CGETSET_MAGIC_DEF("materialCount", js_Model_get, js_Model_set, 2),
    JS_CGETSET_MAGIC_DEF("meshes", js_Model_get, js_Model_set, 3),
    JS_CGETSET_MAGIC_DEF("materials", js_Model_get, js_Model_set, 4),
    JS_CGETSET_MAGIC_DEF("meshMaterial", js_Model_get, js_Model_set, 5),
    JS_CGETSET_MAGIC_DEF("boneCount", js_Model_get, js_Model_set, 6),
    JS_CGETSET_MAGIC_DEF("bones", js_Model_get, js_Model_set, 7),
    JS_CGETSET_MAGIC_DEF("bindPose", js_Model_get, js_Model_set, 8),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Model", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Model(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Model_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Model_class_id, &js_Model_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Model_proto_funcs, countof(js_Model_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Model_ctor, "Model", 9, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Model_class_id, proto);

    JS_SetModuleExport(ctx, m, "Model", class);
    return 0;
}



static JSClassID js_ModelAnimation_class_id;

static JSValue js_ModelAnimation_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    ModelAnimation *s = JS_GetOpaque2(ctx, this_val, js_ModelAnimation_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewInt32(ctx, (int) s->boneCount);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->frameCount);
}

            
            
            

    return JS_UNDEFINED;
}

static JSValue js_ModelAnimation_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    ModelAnimation *s = JS_GetOpaque2(ctx, this_val, js_ModelAnimation_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    int v0;
    if (JS_ToInt32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->boneCount = (int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->frameCount = (int) v1;
}

            
            
            
    
    return JS_UNDEFINED;
}

static void js_ModelAnimation_finalizer(JSRuntime *rt, JSValue val)
{
    ModelAnimation *s = JS_GetOpaque(val, js_ModelAnimation_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_ModelAnimation_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_ModelAnimation_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    ModelAnimation *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
int v0;
if (JS_ToInt32(ctx, &v0, argv[0]))
        goto fail;
s->boneCount = (int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->frameCount = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

            
            
            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_ModelAnimation_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_ModelAnimation_class = {
    "ModelAnimation",
    .finalizer = js_ModelAnimation_finalizer,
};

static const JSCFunctionListEntry js_ModelAnimation_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("boneCount", js_ModelAnimation_get, js_ModelAnimation_set, 0),
    JS_CGETSET_MAGIC_DEF("frameCount", js_ModelAnimation_get, js_ModelAnimation_set, 1),
    JS_CGETSET_MAGIC_DEF("bones", js_ModelAnimation_get, js_ModelAnimation_set, 2),
    JS_CGETSET_MAGIC_DEF("framePoses", js_ModelAnimation_get, js_ModelAnimation_set, 3),
    JS_CGETSET_MAGIC_DEF("name", js_ModelAnimation_get, js_ModelAnimation_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "ModelAnimation", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_ModelAnimation(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_ModelAnimation_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_ModelAnimation_class_id, &js_ModelAnimation_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_ModelAnimation_proto_funcs, countof(js_ModelAnimation_proto_funcs));

    class = JS_NewCFunction2(ctx, js_ModelAnimation_ctor, "ModelAnimation", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_ModelAnimation_class_id, proto);

    JS_SetModuleExport(ctx, m, "ModelAnimation", class);
    return 0;
}



static JSClassID js_Ray_class_id;

static JSValue js_Ray_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Ray *s = JS_GetOpaque2(ctx, this_val, js_Ray_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->position;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->direction;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_Ray_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Ray *s = JS_GetOpaque2(ctx, this_val, js_Ray_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->position = *argptr0;
}

if (magic == 1) {
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->direction = *argptr1;
}

    
    return JS_UNDEFINED;
}

static void js_Ray_finalizer(JSRuntime *rt, JSValue val)
{
    Ray *s = JS_GetOpaque(val, js_Ray_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Ray_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Ray_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Ray *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->position = *argptr0;

    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->direction = *argptr1;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Ray_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Ray_class = {
    "Ray",
    .finalizer = js_Ray_finalizer,
};

static const JSCFunctionListEntry js_Ray_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("position", js_Ray_get, js_Ray_set, 0),
    JS_CGETSET_MAGIC_DEF("direction", js_Ray_get, js_Ray_set, 1),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Ray", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Ray(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Ray_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Ray_class_id, &js_Ray_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Ray_proto_funcs, countof(js_Ray_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Ray_ctor, "Ray", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Ray_class_id, proto);

    JS_SetModuleExport(ctx, m, "Ray", class);
    return 0;
}



static JSClassID js_RayCollision_class_id;

static JSValue js_RayCollision_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    RayCollision *s = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewInt32(ctx, (JS_BOOL) s->hit);
}

if (magic == 1) {
    return JS_NewFloat64(ctx, (double) s->distance);
}

if (magic == 2) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->point;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 3) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->normal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_RayCollision_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    RayCollision *s = JS_GetOpaque2(ctx, this_val, js_RayCollision_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    JS_BOOL v0;
    if (JS_ToInt32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->hit = (bool) v0;
}

if (magic == 1) {
    double v1;
    if (JS_ToFloat64(ctx, &v1, val))
        return JS_EXCEPTION;
    s->distance = (float) v1;
}

if (magic == 2) {
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->point = *argptr2;
}

if (magic == 3) {
    Vector3 * argptr3 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr3 == NULL) return JS_EXCEPTION;
                    
    s->normal = *argptr3;
}

    
    return JS_UNDEFINED;
}

static void js_RayCollision_finalizer(JSRuntime *rt, JSValue val)
{
    RayCollision *s = JS_GetOpaque(val, js_RayCollision_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_RayCollision_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_RayCollision_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    RayCollision *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
JS_BOOL v0;
if (JS_ToInt32(ctx, &v0, argv[0]))
        goto fail;
s->hit = (bool) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

double v1;
if (JS_ToFloat64(ctx, &v1, argv[1]))
        goto fail;
s->distance = (float) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
                    
    if (argptr2 == NULL) return JS_EXCEPTION;
                    
    s->point = *argptr2;

    Vector3 * argptr3 = (Vector3 *)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
                    
    if (argptr3 == NULL) return JS_EXCEPTION;
                    
    s->normal = *argptr3;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_RayCollision_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_RayCollision_class = {
    "RayCollision",
    .finalizer = js_RayCollision_finalizer,
};

static const JSCFunctionListEntry js_RayCollision_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("hit", js_RayCollision_get, js_RayCollision_set, 0),
    JS_CGETSET_MAGIC_DEF("distance", js_RayCollision_get, js_RayCollision_set, 1),
    JS_CGETSET_MAGIC_DEF("point", js_RayCollision_get, js_RayCollision_set, 2),
    JS_CGETSET_MAGIC_DEF("normal", js_RayCollision_get, js_RayCollision_set, 3),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "RayCollision", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_RayCollision(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_RayCollision_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_RayCollision_class_id, &js_RayCollision_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_RayCollision_proto_funcs, countof(js_RayCollision_proto_funcs));

    class = JS_NewCFunction2(ctx, js_RayCollision_ctor, "RayCollision", 4, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_RayCollision_class_id, proto);

    JS_SetModuleExport(ctx, m, "RayCollision", class);
    return 0;
}



static JSClassID js_BoundingBox_class_id;

static JSValue js_BoundingBox_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    BoundingBox *s = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->min;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = s->max;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}


    return JS_UNDEFINED;
}

static JSValue js_BoundingBox_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    BoundingBox *s = JS_GetOpaque2(ctx, this_val, js_BoundingBox_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->min = *argptr0;
}

if (magic == 1) {
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, val, js_Vector3_class_id);
    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->max = *argptr1;
}

    
    return JS_UNDEFINED;
}

static void js_BoundingBox_finalizer(JSRuntime *rt, JSValue val)
{
    BoundingBox *s = JS_GetOpaque(val, js_BoundingBox_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_BoundingBox_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_BoundingBox_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    BoundingBox *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->min = *argptr0;

    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
                    
    if (argptr1 == NULL) return JS_EXCEPTION;
                    
    s->max = *argptr1;

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_BoundingBox_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_BoundingBox_class = {
    "BoundingBox",
    .finalizer = js_BoundingBox_finalizer,
};

static const JSCFunctionListEntry js_BoundingBox_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("min", js_BoundingBox_get, js_BoundingBox_set, 0),
    JS_CGETSET_MAGIC_DEF("max", js_BoundingBox_get, js_BoundingBox_set, 1),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "BoundingBox", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_BoundingBox(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_BoundingBox_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_BoundingBox_class_id, &js_BoundingBox_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_BoundingBox_proto_funcs, countof(js_BoundingBox_proto_funcs));

    class = JS_NewCFunction2(ctx, js_BoundingBox_ctor, "BoundingBox", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_BoundingBox_class_id, proto);

    JS_SetModuleExport(ctx, m, "BoundingBox", class);
    return 0;
}



static JSClassID js_Wave_class_id;

static JSValue js_Wave_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Wave *s = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->frameCount);
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->sampleRate);
}

if (magic == 2) {
    return JS_NewUint32(ctx, (unsigned int) s->sampleSize);
}

if (magic == 3) {
    return JS_NewUint32(ctx, (unsigned int) s->channels);
}

if (magic == 4) {
    return JS_NewUint32(ctx, (unsigned int) s->data);
}


    return JS_UNDEFINED;
}

static JSValue js_Wave_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Wave *s = JS_GetOpaque2(ctx, this_val, js_Wave_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->frameCount = (unsigned int) v0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->sampleRate = (unsigned int) v1;
}

if (magic == 2) {
    unsigned int v2;
    if (JS_ToUint32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->sampleSize = (unsigned int) v2;
}

if (magic == 3) {
    unsigned int v3;
    if (JS_ToUint32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->channels = (unsigned int) v3;
}

if (magic == 4) {
    unsigned int v4;
    if (JS_ToUint32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->data = (void *) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Wave_finalizer(JSRuntime *rt, JSValue val)
{
    Wave *s = JS_GetOpaque(val, js_Wave_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Wave_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Wave_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Wave *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->frameCount = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->sampleRate = (unsigned int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

unsigned int v2;
if (JS_ToUint32(ctx, &v2, argv[2]))
        goto fail;
s->sampleSize = (unsigned int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

unsigned int v3;
if (JS_ToUint32(ctx, &v3, argv[3]))
        goto fail;
s->channels = (unsigned int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

unsigned int v4;
if (JS_ToUint32(ctx, &v4, argv[4]))
        goto fail;
s->data = (void *) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Wave_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Wave_class = {
    "Wave",
    .finalizer = js_Wave_finalizer,
};

static const JSCFunctionListEntry js_Wave_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("frameCount", js_Wave_get, js_Wave_set, 0),
    JS_CGETSET_MAGIC_DEF("sampleRate", js_Wave_get, js_Wave_set, 1),
    JS_CGETSET_MAGIC_DEF("sampleSize", js_Wave_get, js_Wave_set, 2),
    JS_CGETSET_MAGIC_DEF("channels", js_Wave_get, js_Wave_set, 3),
    JS_CGETSET_MAGIC_DEF("data", js_Wave_get, js_Wave_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Wave", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Wave(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Wave_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Wave_class_id, &js_Wave_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Wave_proto_funcs, countof(js_Wave_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Wave_ctor, "Wave", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Wave_class_id, proto);

    JS_SetModuleExport(ctx, m, "Wave", class);
    return 0;
}



static JSClassID js_AudioStream_class_id;

static JSValue js_AudioStream_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    AudioStream *s = JS_GetOpaque2(ctx, this_val, js_AudioStream_class_id);
    if (!s)
        return JS_EXCEPTION;

    
            
            
if (magic == 2) {
    return JS_NewUint32(ctx, (unsigned int) s->sampleRate);
}

if (magic == 3) {
    return JS_NewUint32(ctx, (unsigned int) s->sampleSize);
}

if (magic == 4) {
    return JS_NewUint32(ctx, (unsigned int) s->channels);
}


    return JS_UNDEFINED;
}

static JSValue js_AudioStream_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    AudioStream *s = JS_GetOpaque2(ctx, this_val, js_AudioStream_class_id);
    if (!s)
        return JS_EXCEPTION;

    
            
            
if (magic == 2) {
    unsigned int v2;
    if (JS_ToUint32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->sampleRate = (unsigned int) v2;
}

if (magic == 3) {
    unsigned int v3;
    if (JS_ToUint32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->sampleSize = (unsigned int) v3;
}

if (magic == 4) {
    unsigned int v4;
    if (JS_ToUint32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->channels = (unsigned int) v4;
}

    
    return JS_UNDEFINED;
}

static void js_AudioStream_finalizer(JSRuntime *rt, JSValue val)
{
    AudioStream *s = JS_GetOpaque(val, js_AudioStream_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_AudioStream_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_AudioStream_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    AudioStream *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
            
            
unsigned int v2;
if (JS_ToUint32(ctx, &v2, argv[2]))
        goto fail;
s->sampleRate = (unsigned int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

unsigned int v3;
if (JS_ToUint32(ctx, &v3, argv[3]))
        goto fail;
s->sampleSize = (unsigned int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

unsigned int v4;
if (JS_ToUint32(ctx, &v4, argv[4]))
        goto fail;
s->channels = (unsigned int) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_AudioStream_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_AudioStream_class = {
    "AudioStream",
    .finalizer = js_AudioStream_finalizer,
};

static const JSCFunctionListEntry js_AudioStream_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("buffer", js_AudioStream_get, js_AudioStream_set, 0),
    JS_CGETSET_MAGIC_DEF("processor", js_AudioStream_get, js_AudioStream_set, 1),
    JS_CGETSET_MAGIC_DEF("sampleRate", js_AudioStream_get, js_AudioStream_set, 2),
    JS_CGETSET_MAGIC_DEF("sampleSize", js_AudioStream_get, js_AudioStream_set, 3),
    JS_CGETSET_MAGIC_DEF("channels", js_AudioStream_get, js_AudioStream_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "AudioStream", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_AudioStream(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_AudioStream_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_AudioStream_class_id, &js_AudioStream_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_AudioStream_proto_funcs, countof(js_AudioStream_proto_funcs));

    class = JS_NewCFunction2(ctx, js_AudioStream_ctor, "AudioStream", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_AudioStream_class_id, proto);

    JS_SetModuleExport(ctx, m, "AudioStream", class);
    return 0;
}



static JSClassID js_Sound_class_id;

static JSValue js_Sound_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Sound *s = JS_GetOpaque2(ctx, this_val, js_Sound_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    AudioStream* ret_ptr = (AudioStream *)js_malloc(ctx, sizeof(AudioStream));
    *ret_ptr = s->stream;
    JSValue ret = JS_NewObjectClass(ctx, js_AudioStream_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->frameCount);
}


    return JS_UNDEFINED;
}

static JSValue js_Sound_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Sound *s = JS_GetOpaque2(ctx, this_val, js_Sound_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, val, js_AudioStream_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->stream = *argptr0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->frameCount = (unsigned int) v1;
}

    
    return JS_UNDEFINED;
}

static void js_Sound_finalizer(JSRuntime *rt, JSValue val)
{
    Sound *s = JS_GetOpaque(val, js_Sound_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Sound_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Sound_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Sound *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->stream = *argptr0;

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->frameCount = (unsigned int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Sound_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Sound_class = {
    "Sound",
    .finalizer = js_Sound_finalizer,
};

static const JSCFunctionListEntry js_Sound_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("stream", js_Sound_get, js_Sound_set, 0),
    JS_CGETSET_MAGIC_DEF("frameCount", js_Sound_get, js_Sound_set, 1),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Sound", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Sound(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Sound_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Sound_class_id, &js_Sound_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Sound_proto_funcs, countof(js_Sound_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Sound_ctor, "Sound", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Sound_class_id, proto);

    JS_SetModuleExport(ctx, m, "Sound", class);
    return 0;
}



static JSClassID js_Music_class_id;

static JSValue js_Music_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    Music *s = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    AudioStream* ret_ptr = (AudioStream *)js_malloc(ctx, sizeof(AudioStream));
    *ret_ptr = s->stream;
    JSValue ret = JS_NewObjectClass(ctx, js_AudioStream_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->frameCount);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (JS_BOOL) s->looping);
}

if (magic == 3) {
    return JS_NewInt32(ctx, (int) s->ctxType);
}

if (magic == 4) {
    return JS_NewUint32(ctx, (unsigned int) s->ctxData);
}


    return JS_UNDEFINED;
}

static JSValue js_Music_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    Music *s = JS_GetOpaque2(ctx, this_val, js_Music_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, val, js_AudioStream_class_id);
    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->stream = *argptr0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->frameCount = (unsigned int) v1;
}

if (magic == 2) {
    JS_BOOL v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->looping = (bool) v2;
}

if (magic == 3) {
    int v3;
    if (JS_ToInt32(ctx, &v3, val))
        return JS_EXCEPTION;
    s->ctxType = (int) v3;
}

if (magic == 4) {
    unsigned int v4;
    if (JS_ToUint32(ctx, &v4, val))
        return JS_EXCEPTION;
    s->ctxData = (void *) v4;
}

    
    return JS_UNDEFINED;
}

static void js_Music_finalizer(JSRuntime *rt, JSValue val)
{
    Music *s = JS_GetOpaque(val, js_Music_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_Music_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_Music_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    Music *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
                    
    if (argptr0 == NULL) return JS_EXCEPTION;
                    
    s->stream = *argptr0;

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->frameCount = (unsigned int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

JS_BOOL v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->looping = (bool) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

int v3;
if (JS_ToInt32(ctx, &v3, argv[3]))
        goto fail;
s->ctxType = (int) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

unsigned int v4;
if (JS_ToUint32(ctx, &v4, argv[4]))
        goto fail;
s->ctxData = (void *) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_Music_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_Music_class = {
    "Music",
    .finalizer = js_Music_finalizer,
};

static const JSCFunctionListEntry js_Music_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("stream", js_Music_get, js_Music_set, 0),
    JS_CGETSET_MAGIC_DEF("frameCount", js_Music_get, js_Music_set, 1),
    JS_CGETSET_MAGIC_DEF("looping", js_Music_get, js_Music_set, 2),
    JS_CGETSET_MAGIC_DEF("ctxType", js_Music_get, js_Music_set, 3),
    JS_CGETSET_MAGIC_DEF("ctxData", js_Music_get, js_Music_set, 4),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "Music", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_Music(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_Music_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_Music_class_id, &js_Music_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_Music_proto_funcs, countof(js_Music_proto_funcs));

    class = JS_NewCFunction2(ctx, js_Music_ctor, "Music", 5, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_Music_class_id, proto);

    JS_SetModuleExport(ctx, m, "Music", class);
    return 0;
}



static JSClassID js_VrDeviceInfo_class_id;

static JSValue js_VrDeviceInfo_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    VrDeviceInfo *s = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewInt32(ctx, (int) s->hResolution);
}

if (magic == 1) {
    return JS_NewInt32(ctx, (int) s->vResolution);
}

if (magic == 2) {
    return JS_NewFloat64(ctx, (double) s->hScreenSize);
}

if (magic == 3) {
    return JS_NewFloat64(ctx, (double) s->vScreenSize);
}

if (magic == 4) {
    return JS_NewFloat64(ctx, (double) s->vScreenCenter);
}

if (magic == 5) {
    return JS_NewFloat64(ctx, (double) s->eyeToScreenDistance);
}

if (magic == 6) {
    return JS_NewFloat64(ctx, (double) s->lensSeparationDistance);
}

if (magic == 7) {
    return JS_NewFloat64(ctx, (double) s->interpupillaryDistance);
}

            
            

    return JS_UNDEFINED;
}

static JSValue js_VrDeviceInfo_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    VrDeviceInfo *s = JS_GetOpaque2(ctx, this_val, js_VrDeviceInfo_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    int v0;
    if (JS_ToInt32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->hResolution = (int) v0;
}

if (magic == 1) {
    int v1;
    if (JS_ToInt32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->vResolution = (int) v1;
}

if (magic == 2) {
    double v2;
    if (JS_ToFloat64(ctx, &v2, val))
        return JS_EXCEPTION;
    s->hScreenSize = (float) v2;
}

if (magic == 3) {
    double v3;
    if (JS_ToFloat64(ctx, &v3, val))
        return JS_EXCEPTION;
    s->vScreenSize = (float) v3;
}

if (magic == 4) {
    double v4;
    if (JS_ToFloat64(ctx, &v4, val))
        return JS_EXCEPTION;
    s->vScreenCenter = (float) v4;
}

if (magic == 5) {
    double v5;
    if (JS_ToFloat64(ctx, &v5, val))
        return JS_EXCEPTION;
    s->eyeToScreenDistance = (float) v5;
}

if (magic == 6) {
    double v6;
    if (JS_ToFloat64(ctx, &v6, val))
        return JS_EXCEPTION;
    s->lensSeparationDistance = (float) v6;
}

if (magic == 7) {
    double v7;
    if (JS_ToFloat64(ctx, &v7, val))
        return JS_EXCEPTION;
    s->interpupillaryDistance = (float) v7;
}

            
            
    
    return JS_UNDEFINED;
}

static void js_VrDeviceInfo_finalizer(JSRuntime *rt, JSValue val)
{
    VrDeviceInfo *s = JS_GetOpaque(val, js_VrDeviceInfo_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_VrDeviceInfo_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_VrDeviceInfo_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    VrDeviceInfo *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
int v0;
if (JS_ToInt32(ctx, &v0, argv[0]))
        goto fail;
s->hResolution = (int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

int v1;
if (JS_ToInt32(ctx, &v1, argv[1]))
        goto fail;
s->vResolution = (int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

double v2;
if (JS_ToFloat64(ctx, &v2, argv[2]))
        goto fail;
s->hScreenSize = (float) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

double v3;
if (JS_ToFloat64(ctx, &v3, argv[3]))
        goto fail;
s->vScreenSize = (float) v3;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 3 = %lf", s->3);*/
        

double v4;
if (JS_ToFloat64(ctx, &v4, argv[4]))
        goto fail;
s->vScreenCenter = (float) v4;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 4 = %lf", s->4);*/
        

double v5;
if (JS_ToFloat64(ctx, &v5, argv[5]))
        goto fail;
s->eyeToScreenDistance = (float) v5;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 5 = %lf", s->5);*/
        

double v6;
if (JS_ToFloat64(ctx, &v6, argv[6]))
        goto fail;
s->lensSeparationDistance = (float) v6;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 6 = %lf", s->6);*/
        

double v7;
if (JS_ToFloat64(ctx, &v7, argv[7]))
        goto fail;
s->interpupillaryDistance = (float) v7;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 7 = %lf", s->7);*/
        

            
            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_VrDeviceInfo_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_VrDeviceInfo_class = {
    "VrDeviceInfo",
    .finalizer = js_VrDeviceInfo_finalizer,
};

static const JSCFunctionListEntry js_VrDeviceInfo_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("hResolution", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 0),
    JS_CGETSET_MAGIC_DEF("vResolution", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 1),
    JS_CGETSET_MAGIC_DEF("hScreenSize", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 2),
    JS_CGETSET_MAGIC_DEF("vScreenSize", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 3),
    JS_CGETSET_MAGIC_DEF("vScreenCenter", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 4),
    JS_CGETSET_MAGIC_DEF("eyeToScreenDistance", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 5),
    JS_CGETSET_MAGIC_DEF("lensSeparationDistance", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 6),
    JS_CGETSET_MAGIC_DEF("interpupillaryDistance", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 7),
    JS_CGETSET_MAGIC_DEF("lensDistortionValues", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 8),
    JS_CGETSET_MAGIC_DEF("chromaAbCorrection", js_VrDeviceInfo_get, js_VrDeviceInfo_set, 9),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "VrDeviceInfo", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_VrDeviceInfo(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_VrDeviceInfo_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_VrDeviceInfo_class_id, &js_VrDeviceInfo_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_VrDeviceInfo_proto_funcs, countof(js_VrDeviceInfo_proto_funcs));

    class = JS_NewCFunction2(ctx, js_VrDeviceInfo_ctor, "VrDeviceInfo", 10, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_VrDeviceInfo_class_id, proto);

    JS_SetModuleExport(ctx, m, "VrDeviceInfo", class);
    return 0;
}



static JSClassID js_VrStereoConfig_class_id;

static JSValue js_VrStereoConfig_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    VrStereoConfig *s = JS_GetOpaque2(ctx, this_val, js_VrStereoConfig_class_id);
    if (!s)
        return JS_EXCEPTION;

    
            
            
            
            
            
            
            
            

    return JS_UNDEFINED;
}

static JSValue js_VrStereoConfig_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    VrStereoConfig *s = JS_GetOpaque2(ctx, this_val, js_VrStereoConfig_class_id);
    if (!s)
        return JS_EXCEPTION;

    
            
            
            
            
            
            
            
            
    
    return JS_UNDEFINED;
}

static void js_VrStereoConfig_finalizer(JSRuntime *rt, JSValue val)
{
    VrStereoConfig *s = JS_GetOpaque(val, js_VrStereoConfig_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_VrStereoConfig_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_VrStereoConfig_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    VrStereoConfig *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
            
            
            
            
            
            
            
            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_VrStereoConfig_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_VrStereoConfig_class = {
    "VrStereoConfig",
    .finalizer = js_VrStereoConfig_finalizer,
};

static const JSCFunctionListEntry js_VrStereoConfig_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("projection", js_VrStereoConfig_get, js_VrStereoConfig_set, 0),
    JS_CGETSET_MAGIC_DEF("viewOffset", js_VrStereoConfig_get, js_VrStereoConfig_set, 1),
    JS_CGETSET_MAGIC_DEF("leftLensCenter", js_VrStereoConfig_get, js_VrStereoConfig_set, 2),
    JS_CGETSET_MAGIC_DEF("rightLensCenter", js_VrStereoConfig_get, js_VrStereoConfig_set, 3),
    JS_CGETSET_MAGIC_DEF("leftScreenCenter", js_VrStereoConfig_get, js_VrStereoConfig_set, 4),
    JS_CGETSET_MAGIC_DEF("rightScreenCenter", js_VrStereoConfig_get, js_VrStereoConfig_set, 5),
    JS_CGETSET_MAGIC_DEF("scale", js_VrStereoConfig_get, js_VrStereoConfig_set, 6),
    JS_CGETSET_MAGIC_DEF("scaleIn", js_VrStereoConfig_get, js_VrStereoConfig_set, 7),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "VrStereoConfig", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_VrStereoConfig(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_VrStereoConfig_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_VrStereoConfig_class_id, &js_VrStereoConfig_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_VrStereoConfig_proto_funcs, countof(js_VrStereoConfig_proto_funcs));

    class = JS_NewCFunction2(ctx, js_VrStereoConfig_ctor, "VrStereoConfig", 8, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_VrStereoConfig_class_id, proto);

    JS_SetModuleExport(ctx, m, "VrStereoConfig", class);
    return 0;
}



static JSClassID js_FilePathList_class_id;

static JSValue js_FilePathList_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    FilePathList *s = JS_GetOpaque2(ctx, this_val, js_FilePathList_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->capacity);
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->count);
}

            

    return JS_UNDEFINED;
}

static JSValue js_FilePathList_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    FilePathList *s = JS_GetOpaque2(ctx, this_val, js_FilePathList_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->capacity = (unsigned int) v0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->count = (unsigned int) v1;
}

            
    
    return JS_UNDEFINED;
}

static void js_FilePathList_finalizer(JSRuntime *rt, JSValue val)
{
    FilePathList *s = JS_GetOpaque(val, js_FilePathList_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_FilePathList_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_FilePathList_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    FilePathList *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->capacity = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->count = (unsigned int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_FilePathList_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_FilePathList_class = {
    "FilePathList",
    .finalizer = js_FilePathList_finalizer,
};

static const JSCFunctionListEntry js_FilePathList_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("capacity", js_FilePathList_get, js_FilePathList_set, 0),
    JS_CGETSET_MAGIC_DEF("count", js_FilePathList_get, js_FilePathList_set, 1),
    JS_CGETSET_MAGIC_DEF("paths", js_FilePathList_get, js_FilePathList_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "FilePathList", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_FilePathList(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_FilePathList_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_FilePathList_class_id, &js_FilePathList_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_FilePathList_proto_funcs, countof(js_FilePathList_proto_funcs));

    class = JS_NewCFunction2(ctx, js_FilePathList_ctor, "FilePathList", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_FilePathList_class_id, proto);

    JS_SetModuleExport(ctx, m, "FilePathList", class);
    return 0;
}



static JSClassID js_AutomationEvent_class_id;

static JSValue js_AutomationEvent_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    AutomationEvent *s = JS_GetOpaque2(ctx, this_val, js_AutomationEvent_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->frame);
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->type);
}

            

    return JS_UNDEFINED;
}

static JSValue js_AutomationEvent_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    AutomationEvent *s = JS_GetOpaque2(ctx, this_val, js_AutomationEvent_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->frame = (unsigned int) v0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->type = (unsigned int) v1;
}

            
    
    return JS_UNDEFINED;
}

static void js_AutomationEvent_finalizer(JSRuntime *rt, JSValue val)
{
    AutomationEvent *s = JS_GetOpaque(val, js_AutomationEvent_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_AutomationEvent_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_AutomationEvent_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    AutomationEvent *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->frame = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->type = (unsigned int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_AutomationEvent_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_AutomationEvent_class = {
    "AutomationEvent",
    .finalizer = js_AutomationEvent_finalizer,
};

static const JSCFunctionListEntry js_AutomationEvent_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("frame", js_AutomationEvent_get, js_AutomationEvent_set, 0),
    JS_CGETSET_MAGIC_DEF("type", js_AutomationEvent_get, js_AutomationEvent_set, 1),
    JS_CGETSET_MAGIC_DEF("params", js_AutomationEvent_get, js_AutomationEvent_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "AutomationEvent", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_AutomationEvent(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_AutomationEvent_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_AutomationEvent_class_id, &js_AutomationEvent_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_AutomationEvent_proto_funcs, countof(js_AutomationEvent_proto_funcs));

    class = JS_NewCFunction2(ctx, js_AutomationEvent_ctor, "AutomationEvent", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_AutomationEvent_class_id, proto);

    JS_SetModuleExport(ctx, m, "AutomationEvent", class);
    return 0;
}



static JSClassID js_AutomationEventList_class_id;

static JSValue js_AutomationEventList_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    AutomationEventList *s = JS_GetOpaque2(ctx, this_val, js_AutomationEventList_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned int) s->capacity);
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned int) s->count);
}

            

    return JS_UNDEFINED;
}

static JSValue js_AutomationEventList_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    AutomationEventList *s = JS_GetOpaque2(ctx, this_val, js_AutomationEventList_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned int v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->capacity = (unsigned int) v0;
}

if (magic == 1) {
    unsigned int v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->count = (unsigned int) v1;
}

            
    
    return JS_UNDEFINED;
}

static void js_AutomationEventList_finalizer(JSRuntime *rt, JSValue val)
{
    AutomationEventList *s = JS_GetOpaque(val, js_AutomationEventList_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_AutomationEventList_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_AutomationEventList_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    AutomationEventList *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned int v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->capacity = (unsigned int) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

unsigned int v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->count = (unsigned int) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

            
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_AutomationEventList_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_AutomationEventList_class = {
    "AutomationEventList",
    .finalizer = js_AutomationEventList_finalizer,
};

static const JSCFunctionListEntry js_AutomationEventList_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("capacity", js_AutomationEventList_get, js_AutomationEventList_set, 0),
    JS_CGETSET_MAGIC_DEF("count", js_AutomationEventList_get, js_AutomationEventList_set, 1),
    JS_CGETSET_MAGIC_DEF("events", js_AutomationEventList_get, js_AutomationEventList_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "AutomationEventList", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_AutomationEventList(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_AutomationEventList_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_AutomationEventList_class_id, &js_AutomationEventList_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_AutomationEventList_proto_funcs, countof(js_AutomationEventList_proto_funcs));

    class = JS_NewCFunction2(ctx, js_AutomationEventList_ctor, "AutomationEventList", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_AutomationEventList_class_id, proto);

    JS_SetModuleExport(ctx, m, "AutomationEventList", class);
    return 0;
}

static JSValue js_InitWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);

    InitWindow(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg2);

    return JS_UNDEFINED;
}

static JSValue js_CloseWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    CloseWindow();


    return JS_UNDEFINED;
}

static JSValue js_WindowShouldClose(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = WindowShouldClose();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowReady();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowFullscreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowFullscreen();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowHidden(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowHidden();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowMinimized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowMinimized();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowMaximized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowMaximized();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowFocused(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowFocused();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowResized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsWindowResized();


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsWindowState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    bool ret = IsWindowState(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_SetWindowState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    SetWindowState(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ClearWindowState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    ClearWindowState(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ToggleFullscreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    ToggleFullscreen();


    return JS_UNDEFINED;
}

static JSValue js_ToggleBorderlessWindowed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    ToggleBorderlessWindowed();


    return JS_UNDEFINED;
}

static JSValue js_MaximizeWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    MaximizeWindow();


    return JS_UNDEFINED;
}

static JSValue js_MinimizeWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    MinimizeWindow();


    return JS_UNDEFINED;
}

static JSValue js_RestoreWindow(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    RestoreWindow();


    return JS_UNDEFINED;
}

static JSValue js_SetWindowIcon(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;

    SetWindowIcon(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowTitle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    SetWindowTitle(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_SetWindowPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetWindowPosition(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowMonitor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetWindowMonitor(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowMinSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetWindowMinSize(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowMaxSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetWindowMaxSize(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetWindowSize(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowOpacity(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);

    SetWindowOpacity(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SetWindowFocused(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    SetWindowFocused();


    return JS_UNDEFINED;
}

static JSValue js_GetWindowHandle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    void * ret = GetWindowHandle();


    return JS_NewUint32(ctx, (unsigned int) ret);
}

static JSValue js_GetScreenWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetScreenWidth();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetScreenHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetScreenHeight();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetRenderWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetRenderWidth();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetRenderHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetRenderHeight();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMonitorCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetMonitorCount();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetCurrentMonitor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetCurrentMonitor();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMonitorPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    Vector2 returnVal = GetMonitorPosition(arg0);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetMonitorWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetMonitorWidth(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMonitorHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetMonitorHeight(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMonitorPhysicalWidth(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetMonitorPhysicalWidth(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMonitorPhysicalHeight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetMonitorPhysicalHeight(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMonitorRefreshRate(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetMonitorRefreshRate(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetWindowPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetWindowPosition();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetWindowScaleDPI(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetWindowScaleDPI();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetMonitorName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    const char * returnVal = GetMonitorName(arg0);


    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_SetClipboardText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    SetClipboardText(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_GetClipboardText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    const char * returnVal = GetClipboardText();


    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_EnableEventWaiting(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EnableEventWaiting();


    return JS_UNDEFINED;
}

static JSValue js_DisableEventWaiting(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    DisableEventWaiting();


    return JS_UNDEFINED;
}

static JSValue js_ShowCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    ShowCursor();


    return JS_UNDEFINED;
}

static JSValue js_HideCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    HideCursor();


    return JS_UNDEFINED;
}

static JSValue js_IsCursorHidden(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsCursorHidden();


    return JS_NewBool(ctx, ret);
}

static JSValue js_EnableCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EnableCursor();


    return JS_UNDEFINED;
}

static JSValue js_DisableCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    DisableCursor();


    return JS_UNDEFINED;
}

static JSValue js_IsCursorOnScreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsCursorOnScreen();


    return JS_NewBool(ctx, ret);
}

static JSValue js_ClearBackground(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;

    ClearBackground(arg0);


    return JS_UNDEFINED;
}

static JSValue js_BeginDrawing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    BeginDrawing();


    return JS_UNDEFINED;
}

static JSValue js_EndDrawing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndDrawing();


    return JS_UNDEFINED;
}

static JSValue js_BeginMode2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera2D * argptr0 = (Camera2D *)JS_GetOpaque2(ctx, argv[0], js_Camera2D_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera2D arg0 = *argptr0;

    BeginMode2D(arg0);


    return JS_UNDEFINED;
}

static JSValue js_EndMode2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndMode2D();


    return JS_UNDEFINED;
}

static JSValue js_BeginMode3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera3D * argptr0 = (Camera3D *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Camera3D *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera3D arg0 = *argptr0;

    BeginMode3D(arg0);


    return JS_UNDEFINED;
}

static JSValue js_EndMode3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndMode3D();


    return JS_UNDEFINED;
}

static JSValue js_BeginTextureMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    RenderTexture2D * argptr0 = (RenderTexture2D *)JS_GetOpaque2(ctx, argv[0], js_RenderTexture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (RenderTexture2D *)JS_GetOpaque2(ctx, argv[0], js_RenderTexture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        RenderTexture2D arg0 = *argptr0;

    BeginTextureMode(arg0);


    return JS_UNDEFINED;
}

static JSValue js_EndTextureMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndTextureMode();


    return JS_UNDEFINED;
}

static JSValue js_BeginShaderMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;

    BeginShaderMode(arg0);


    return JS_UNDEFINED;
}

static JSValue js_EndShaderMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndShaderMode();


    return JS_UNDEFINED;
}

static JSValue js_BeginBlendMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    BeginBlendMode(arg0);


    return JS_UNDEFINED;
}

static JSValue js_EndBlendMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndBlendMode();


    return JS_UNDEFINED;
}

static JSValue js_BeginScissorMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    BeginScissorMode(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_EndScissorMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndScissorMode();


    return JS_UNDEFINED;
}

static JSValue js_BeginVrStereoMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    VrStereoConfig * argptr0 = (VrStereoConfig *)JS_GetOpaque2(ctx, argv[0], js_VrStereoConfig_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        VrStereoConfig arg0 = *argptr0;

    BeginVrStereoMode(arg0);


    return JS_UNDEFINED;
}

static JSValue js_EndVrStereoMode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    EndVrStereoMode();


    return JS_UNDEFINED;
}

static JSValue js_LoadVrStereoConfig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    VrDeviceInfo * argptr0 = (VrDeviceInfo *)JS_GetOpaque2(ctx, argv[0], js_VrDeviceInfo_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        VrDeviceInfo arg0 = *argptr0;

    VrStereoConfig returnVal = LoadVrStereoConfig(arg0);


    
    VrStereoConfig* ret_ptr = (VrStereoConfig *)js_malloc(ctx, sizeof(VrStereoConfig));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_VrStereoConfig_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_UnloadVrStereoConfig(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    VrStereoConfig * argptr0 = (VrStereoConfig *)JS_GetOpaque2(ctx, argv[0], js_VrStereoConfig_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        VrStereoConfig arg0 = *argptr0;

    UnloadVrStereoConfig(arg0);


    return JS_UNDEFINED;
}

static JSValue js_LoadShader(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    Shader returnVal = LoadShader(arg0, arg1);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    
    Shader* ret_ptr = (Shader *)js_malloc(ctx, sizeof(Shader));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadShaderFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    Shader returnVal = LoadShaderFromMemory(arg0, arg1);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    
    Shader* ret_ptr = (Shader *)js_malloc(ctx, sizeof(Shader));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Shader_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsShaderReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;

    bool ret = IsShaderReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetShaderLocation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GetShaderLocation(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetShaderLocationAttrib(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GetShaderLocationAttrib(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_SetShaderValue(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
size_t data_size2;
    const void * arg2 = (const void *)JS_GetArrayBuffer(ctx, &data_size2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    SetShaderValue(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_SetShaderValueV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
size_t data_size2;
    const void * arg2 = (const void *)JS_GetArrayBuffer(ctx, &data_size2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);

    SetShaderValueV(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_SetShaderValueMatrix(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    Matrix * argptr2 = (Matrix *)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Matrix arg2 = *argptr2;

    SetShaderValueMatrix(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_SetShaderValueTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    Texture2D * argptr2 = (Texture2D *)JS_GetOpaque2(ctx, argv[2], js_Texture2D_class_id);
        if (argptr2 == NULL)
        argptr2 = (Texture2D *)JS_GetOpaque2(ctx, argv[2], js_Texture_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg2 = *argptr2;

    SetShaderValueTexture(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_UnloadShader(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Shader * argptr0 = (Shader *)JS_GetOpaque2(ctx, argv[0], js_Shader_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Shader arg0 = *argptr0;

    UnloadShader(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetMouseRay(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Camera * argptr1 = (Camera *)JS_GetOpaque2(ctx, argv[1], js_Camera_class_id);
        if (argptr1 == NULL)
        argptr1 = (Camera *)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Camera arg1 = *argptr1;

    Ray returnVal = GetMouseRay(arg0, arg1);


    
    Ray* ret_ptr = (Ray *)js_malloc(ctx, sizeof(Ray));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Ray_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetCameraMatrix(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (argptr0 == NULL)
        argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera arg0 = *argptr0;

    Matrix returnVal = GetCameraMatrix(arg0);


    
    Matrix* ret_ptr = (Matrix *)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetCameraMatrix2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera2D * argptr0 = (Camera2D *)JS_GetOpaque2(ctx, argv[0], js_Camera2D_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera2D arg0 = *argptr0;

    Matrix returnVal = GetCameraMatrix2D(arg0);


    
    Matrix* ret_ptr = (Matrix *)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetWorldToScreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Camera * argptr1 = (Camera *)JS_GetOpaque2(ctx, argv[1], js_Camera_class_id);
        if (argptr1 == NULL)
        argptr1 = (Camera *)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Camera arg1 = *argptr1;

    Vector2 returnVal = GetWorldToScreen(arg0, arg1);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetScreenToWorld2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Camera2D * argptr1 = (Camera2D *)JS_GetOpaque2(ctx, argv[1], js_Camera2D_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Camera2D arg1 = *argptr1;

    Vector2 returnVal = GetScreenToWorld2D(arg0, arg1);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetWorldToScreenEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Camera * argptr1 = (Camera *)JS_GetOpaque2(ctx, argv[1], js_Camera_class_id);
        if (argptr1 == NULL)
        argptr1 = (Camera *)JS_GetOpaque2(ctx, argv[1], js_Camera3D_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Camera arg1 = *argptr1;
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    Vector2 returnVal = GetWorldToScreenEx(arg0, arg1, arg2, arg3);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetWorldToScreen2D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Camera2D * argptr1 = (Camera2D *)JS_GetOpaque2(ctx, argv[1], js_Camera2D_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Camera2D arg1 = *argptr1;

    Vector2 returnVal = GetWorldToScreen2D(arg0, arg1);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_SetTargetFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetTargetFPS(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetFrameTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    float ret = GetFrameTime();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_GetTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    double ret = GetTime();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_GetFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetFPS();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_SwapScreenBuffer(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    SwapScreenBuffer();


    return JS_UNDEFINED;
}

static JSValue js_PollInputEvents(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    PollInputEvents();


    return JS_UNDEFINED;
}

static JSValue js_WaitTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);

    WaitTime(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SetRandomSeed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    SetRandomSeed(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetRandomValue(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    int ret = GetRandomValue(arg0, arg1);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_LoadRandomSequence(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    int * retBuf = LoadRandomSequence(arg0, arg1, arg2);


    JSValue ret = JS_NewArray(ctx);
    for(int i; i < 7777 /*<<size>>*/; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewInt32(ctx, retBuf[i]));
    }
        return ret;
        
}

static JSValue js_UnloadRandomSequence(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "sequence");
    int arg0_int;
    JS_ToInt32(ctx, &arg0_int, arg0_js);
    int * arg0 = &arg0_int;
                    
    UnloadRandomSequence(arg0);

JS_SetPropertyStr(ctx, argv[0], "sequence", JS_NewInt32(ctx, arg0_int));

    return JS_UNDEFINED;
}

static JSValue js_TakeScreenshot(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    TakeScreenshot(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_SetConfigFlags(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    SetConfigFlags(arg0);


    return JS_UNDEFINED;
}

static JSValue js_OpenURL(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    OpenURL(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_SetTraceLogLevel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetTraceLogLevel(arg0);


    return JS_UNDEFINED;
}

static JSValue js_MemAlloc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    void * ret = MemAlloc(arg0);


    return JS_NewUint32(ctx, (unsigned int) ret);
}

static JSValue js_MemRealloc(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    void * arg0 = (void *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    unsigned int arg1;
    JS_ToUint32(ctx, &arg1, argv[1]);

    void * ret = MemRealloc(arg0, arg1);


    return JS_NewUint32(ctx, (unsigned int) ret);
}

static JSValue js_MemFree(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    void * arg0 = (void *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);

    MemFree(arg0);


    return JS_UNDEFINED;
}

static JSValue js_LoadFileData(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    size_t data_size1;
    int * arg1 = (int *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);

    unsigned char * retVal = LoadFileData(arg0, &data_size1);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, data_size1);

    UnloadFileData(retVal);
    return ret;
}

static JSValue js_SaveFileData(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
size_t data_size1;
    void * arg1 = (void *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    bool ret = SaveFileData(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);

    return JS_NewBool(ctx, ret);
}

static JSValue js_ExportDataAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    const unsigned char * arg0 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);

    bool ret = ExportDataAsCode(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg2);

    return JS_NewBool(ctx, ret);
}

static JSValue js_LoadFileText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    char * retVal = LoadFileText(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, retVal);

    UnloadFileText(retVal);
    return ret;
}

static JSValue js_UnloadFileText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
return JS_UNDEFINED;
}

static JSValue js_SaveFileText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "text");
    size_t arg1_len;
    const char * arg1_str = JS_ToCStringLen(ctx, &arg1_len, arg1_js);
    char * arg1 = malloc(arg1_len+1);
    memcpy((void *)arg1, arg1_str, arg1_len);
    arg1[arg1_len] = 0;
                
    bool ret = SaveFileText(arg0, arg1);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1_str);
                JS_SetPropertyStr(ctx, argv[1], "text", JS_NewString(ctx, arg1));
                free(arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_FileExists(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    bool ret = FileExists(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewBool(ctx, ret);
}

static JSValue js_DirectoryExists(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    bool ret = DirectoryExists(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewBool(ctx, ret);
}

static JSValue js_IsFileExtension(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = IsFileExtension(arg0, arg1);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_GetFileLength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    int ret = GetFileLength(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetFileExtension(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = GetFileExtension(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetFileName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = GetFileName(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetFileNameWithoutExt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = GetFileNameWithoutExt(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetDirectoryPath(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = GetDirectoryPath(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetPrevDirectoryPath(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = GetPrevDirectoryPath(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetWorkingDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    const char * returnVal = GetWorkingDirectory();


    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GetApplicationDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    const char * returnVal = GetApplicationDirectory();


    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_ChangeDirectory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    bool ret = ChangeDirectory(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewBool(ctx, ret);
}

static JSValue js_IsPathFile(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    bool ret = IsPathFile(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewBool(ctx, ret);
}

static JSValue js_LoadDirectoryFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    FilePathList returnVal = LoadDirectoryFiles(arg0);

    JS_FreeCString(ctx, arg0);

    
    FilePathList* ret_ptr = (FilePathList *)js_malloc(ctx, sizeof(FilePathList));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_FilePathList_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadDirectoryFilesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    JS_BOOL argbool2 = JS_ToBool(ctx, argv[2]);
    bool arg2 = (bool) argbool2;

    FilePathList returnVal = LoadDirectoryFilesEx(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    
    FilePathList* ret_ptr = (FilePathList *)js_malloc(ctx, sizeof(FilePathList));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_FilePathList_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_UnloadDirectoryFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    FilePathList * argptr0 = (FilePathList *)JS_GetOpaque2(ctx, argv[0], js_FilePathList_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        FilePathList arg0 = *argptr0;

    UnloadDirectoryFiles(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsFileDropped(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsFileDropped();


    return JS_NewBool(ctx, ret);
}

static JSValue js_LoadDroppedFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    FilePathList returnVal = LoadDroppedFiles();


    
    FilePathList* ret_ptr = (FilePathList *)js_malloc(ctx, sizeof(FilePathList));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_FilePathList_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_UnloadDroppedFiles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    FilePathList * argptr0 = (FilePathList *)JS_GetOpaque2(ctx, argv[0], js_FilePathList_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        FilePathList arg0 = *argptr0;

    UnloadDroppedFiles(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetFileModTime(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    long ret = GetFileModTime(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewInt64(ctx, ret);
}

static JSValue js_CompressData(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    const unsigned char * arg0 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "compDataSize");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    unsigned char * retVal = CompressData(arg0, arg1, arg2);

JS_SetPropertyStr(ctx, argv[2], "compDataSize", JS_NewInt32(ctx, arg2_int));

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
    return ret;
}

static JSValue js_DecompressData(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    const unsigned char * arg0 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "dataSize");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    unsigned char * retVal = DecompressData(arg0, arg1, arg2);

JS_SetPropertyStr(ctx, argv[2], "dataSize", JS_NewInt32(ctx, arg2_int));

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
    return ret;
}

static JSValue js_EncodeDataBase64(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    const unsigned char * arg0 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "outputSize");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    char * retVal = EncodeDataBase64(arg0, arg1, arg2);

JS_SetPropertyStr(ctx, argv[2], "outputSize", JS_NewInt32(ctx, arg2_int));

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
   return ret;
}

static JSValue js_DecodeDataBase64(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    const unsigned char * arg0 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "outputSize");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    unsigned char * retVal = DecodeDataBase64(arg0, arg1);

JS_SetPropertyStr(ctx, argv[1], "outputSize", JS_NewInt32(ctx, arg1_int));

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
    return ret;
}

static JSValue js_LoadAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    AutomationEventList returnVal = LoadAutomationEventList(arg0);

    JS_FreeCString(ctx, arg0);

    
    AutomationEventList* ret_ptr = (AutomationEventList *)js_malloc(ctx, sizeof(AutomationEventList));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_AutomationEventList_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_UnloadAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AutomationEventList * arg0 = (AutomationEventList *)JS_GetOpaque2(ctx, argv[0], js_AutomationEventList_class_id);

    UnloadAutomationEventList(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ExportAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AutomationEventList * argptr0 = (AutomationEventList *)JS_GetOpaque2(ctx, argv[0], js_AutomationEventList_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AutomationEventList arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportAutomationEventList(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_SetAutomationEventList(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AutomationEventList * arg0 = (AutomationEventList *)JS_GetOpaque2(ctx, argv[0], js_AutomationEventList_class_id);

    SetAutomationEventList(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SetAutomationEventBaseFrame(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetAutomationEventBaseFrame(arg0);


    return JS_UNDEFINED;
}

static JSValue js_StartAutomationEventRecording(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    StartAutomationEventRecording();


    return JS_UNDEFINED;
}

static JSValue js_StopAutomationEventRecording(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    StopAutomationEventRecording();


    return JS_UNDEFINED;
}

static JSValue js_PlayAutomationEvent(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AutomationEvent * argptr0 = (AutomationEvent *)JS_GetOpaque2(ctx, argv[0], js_AutomationEvent_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AutomationEvent arg0 = *argptr0;

    PlayAutomationEvent(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsKeyPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsKeyPressed(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsKeyPressedRepeat(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsKeyPressedRepeat(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsKeyDown(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsKeyDown(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsKeyReleased(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsKeyReleased(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsKeyUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsKeyUp(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetKeyPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetKeyPressed();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetCharPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetCharPressed();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_SetExitKey(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetExitKey(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsGamepadAvailable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsGamepadAvailable(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetGamepadName(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    const char * returnVal = GetGamepadName(arg0);


    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_IsGamepadButtonPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    bool ret = IsGamepadButtonPressed(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsGamepadButtonDown(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    bool ret = IsGamepadButtonDown(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsGamepadButtonReleased(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    bool ret = IsGamepadButtonReleased(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsGamepadButtonUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    bool ret = IsGamepadButtonUp(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetGamepadButtonPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetGamepadButtonPressed();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetGamepadAxisCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetGamepadAxisCount(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetGamepadAxisMovement(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    float ret = GetGamepadAxisMovement(arg0, arg1);


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_SetGamepadMappings(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    int ret = SetGamepadMappings(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_IsMouseButtonPressed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsMouseButtonPressed(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsMouseButtonDown(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsMouseButtonDown(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsMouseButtonReleased(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsMouseButtonReleased(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_IsMouseButtonUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    bool ret = IsMouseButtonUp(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetMouseX(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetMouseX();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMouseY(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetMouseY();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetMousePosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetMousePosition();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetMouseDelta(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetMouseDelta();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_SetMousePosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetMousePosition(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetMouseOffset(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetMouseOffset(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetMouseScale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetMouseScale(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_GetMouseWheelMove(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    float ret = GetMouseWheelMove();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_GetMouseWheelMoveV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetMouseWheelMoveV();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_SetMouseCursor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetMouseCursor(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetTouchX(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetTouchX();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetTouchY(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetTouchY();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetTouchPosition(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    Vector2 returnVal = GetTouchPosition(arg0);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetTouchPointId(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    int ret = GetTouchPointId(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetTouchPointCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetTouchPointCount();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_SetGesturesEnabled(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    SetGesturesEnabled(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsGestureDetected(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    bool ret = IsGestureDetected(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetGestureDetected(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GetGestureDetected();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetGestureHoldDuration(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    float ret = GetGestureHoldDuration();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_GetGestureDragVector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetGestureDragVector();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetGestureDragAngle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    float ret = GetGestureDragAngle();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_GetGesturePinchVector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Vector2 returnVal = GetGesturePinchVector();


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetGesturePinchAngle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    float ret = GetGesturePinchAngle();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_UpdateCamera(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    UpdateCamera(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_UpdateCameraPro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);

    UpdateCameraPro(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_SetShapesTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;

    SetShapesTexture(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawPixel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawPixel(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawPixelV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;

    DrawPixelV(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawLine(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawLineV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawLineV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawLineEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawLineEx(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawLineBezier(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawLineBezier(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawCircle(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircleSector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCircleSector(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircleSectorLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCircleSectorLines(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircleGradient(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawCircleGradient(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircleV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawCircleV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircleLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawCircleLines(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircleLinesV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawCircleLinesV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawEllipse(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawEllipse(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawEllipseLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawEllipseLines(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawRing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    int arg5;
    JS_ToInt32(ctx, &arg5, argv[5]);
    Color * argptr6 = (Color *)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
        if (argptr6 == NULL) return JS_EXCEPTION;
                    
        Color arg6 = *argptr6;

    DrawRing(arg0, arg1, arg2, arg3, arg4, arg5, arg6);


    return JS_UNDEFINED;
}

static JSValue js_DrawRingLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    int arg5;
    JS_ToInt32(ctx, &arg5, argv[5]);
    Color * argptr6 = (Color *)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
        if (argptr6 == NULL) return JS_EXCEPTION;
                    
        Color arg6 = *argptr6;

    DrawRingLines(arg0, arg1, arg2, arg3, arg4, arg5, arg6);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawRectangle(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawRectangleV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;

    DrawRectangleRec(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectanglePro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawRectanglePro(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawRectangleGradientV(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientH(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawRectangleGradientH(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleGradientEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawRectangleGradientEx(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawRectangleLines(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleLinesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawRectangleLinesEx(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRounded(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawRectangleRounded(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawRectangleRoundedLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawRectangleRoundedLines(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawTriangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawTriangle(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawTriangleLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawTriangleLines(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawPoly(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawPoly(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawPolyLines(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawPolyLines(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawPolyLinesEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawPolyLinesEx(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentLinear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawSplineSegmentLinear(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBasis(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawSplineSegmentBasis(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentCatmullRom(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawSplineSegmentCatmullRom(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBezierQuadratic(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawSplineSegmentBezierQuadratic(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawSplineSegmentBezierCubic(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawSplineSegmentBezierCubic(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_GetSplinePointLinear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    Vector2 returnVal = GetSplinePointLinear(arg0, arg1, arg2);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetSplinePointBasis(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);

    Vector2 returnVal = GetSplinePointBasis(arg0, arg1, arg2, arg3, arg4);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetSplinePointCatmullRom(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);

    Vector2 returnVal = GetSplinePointCatmullRom(arg0, arg1, arg2, arg3, arg4);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetSplinePointBezierQuad(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);

    Vector2 returnVal = GetSplinePointBezierQuad(arg0, arg1, arg2, arg3);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetSplinePointBezierCubic(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);

    Vector2 returnVal = GetSplinePointBezierCubic(arg0, arg1, arg2, arg3, arg4);


    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_CheckCollisionRecs(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;

    bool ret = CheckCollisionRecs(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionCircles(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);

    bool ret = CheckCollisionCircles(arg0, arg1, arg2, arg3);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionCircleRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Rectangle * argptr2 = (Rectangle *)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg2 = *argptr2;

    bool ret = CheckCollisionCircleRec(arg0, arg1, arg2);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionPointRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;

    bool ret = CheckCollisionPointRec(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionPointCircle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    bool ret = CheckCollisionPointCircle(arg0, arg1, arg2);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionPointTriangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;

    bool ret = CheckCollisionPointTriangle(arg0, arg1, arg2, arg3);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionPointLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector2 * argptr0 = (Vector2 *)JS_GetOpaque2(ctx, argv[0], js_Vector2_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    bool ret = CheckCollisionPointLine(arg0, arg1, arg2, arg3);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetCollisionRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;

    Rectangle returnVal = GetCollisionRec(arg0, arg1);


    
    Rectangle* ret_ptr = (Rectangle *)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Image returnVal = LoadImage(arg0);

    JS_FreeCString(ctx, arg0);

    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImageRaw(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);

    Image returnVal = LoadImageRaw(arg0, arg1, arg2, arg3, arg4);

    JS_FreeCString(ctx, arg0);

    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImageSvg(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Image returnVal = LoadImageSvg(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);

    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImageAnim(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "frames");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    Image returnVal = LoadImageAnim(arg0, arg1);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[1], "frames", JS_NewInt32(ctx, arg1_int));

    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImageFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
size_t data_size1;
    const unsigned char * arg1 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Image returnVal = LoadImageFromMemory(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);

    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImageFromTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;

    Image returnVal = LoadImageFromTexture(arg0);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadImageFromScreen(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Image returnVal = LoadImageFromScreen();


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsImageReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;

    bool ret = IsImageReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;

    UnloadImage(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ExportImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportImage(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_ExportImageToMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "fileSize");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    unsigned char * retVal = ExportImageToMemory(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "fileSize", JS_NewInt32(ctx, arg2_int));

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
    return ret;
}

static JSValue js_ExportImageAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportImageAsCode(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_GenImageColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    Image returnVal = GenImageColor(arg0, arg1, arg2);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageGradientLinear(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    Image returnVal = GenImageGradientLinear(arg0, arg1, arg2, arg3, arg4);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageGradientRadial(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    Image returnVal = GenImageGradientRadial(arg0, arg1, arg2, arg3, arg4);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageGradientSquare(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    Image returnVal = GenImageGradientSquare(arg0, arg1, arg2, arg3, arg4);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageChecked(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    Image returnVal = GenImageChecked(arg0, arg1, arg2, arg3, arg4, arg5);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageWhiteNoise(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    Image returnVal = GenImageWhiteNoise(arg0, arg1, arg2);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImagePerlinNoise(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);

    Image returnVal = GenImagePerlinNoise(arg0, arg1, arg2, arg3, arg4);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageCellular(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Image returnVal = GenImageCellular(arg0, arg1, arg2);


    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenImageText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);

    Image returnVal = GenImageText(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg2);

    
    Image* ret_ptr = (Image *)js_malloc(ctx, sizeof(Image));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Image_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetImageAlphaBorder(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Rectangle returnVal = GetImageAlphaBorder(arg0, arg1);


    
    Rectangle* ret_ptr = (Rectangle *)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetImageColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Color returnVal = GetImageColor(arg0, arg1, arg2);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Texture2D returnVal = LoadTexture(arg0);

    JS_FreeCString(ctx, arg0);

    
    Texture2D* ret_ptr = (Texture2D *)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture2D_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadTextureFromImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;

    Texture2D returnVal = LoadTextureFromImage(arg0);


    
    Texture2D* ret_ptr = (Texture2D *)js_malloc(ctx, sizeof(Texture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Texture2D_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadTextureCubemap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    TextureCubemap returnVal = LoadTextureCubemap(arg0, arg1);


    
    TextureCubemap* ret_ptr = (TextureCubemap *)js_malloc(ctx, sizeof(TextureCubemap));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_TextureCubemap_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadRenderTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    RenderTexture2D returnVal = LoadRenderTexture(arg0, arg1);


    
    RenderTexture2D* ret_ptr = (RenderTexture2D *)js_malloc(ctx, sizeof(RenderTexture2D));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RenderTexture2D_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsTextureReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;

    bool ret = IsTextureReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;

    UnloadTexture(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsRenderTextureReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    RenderTexture2D * argptr0 = (RenderTexture2D *)JS_GetOpaque2(ctx, argv[0], js_RenderTexture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (RenderTexture2D *)JS_GetOpaque2(ctx, argv[0], js_RenderTexture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        RenderTexture2D arg0 = *argptr0;

    bool ret = IsRenderTextureReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadRenderTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    RenderTexture2D * argptr0 = (RenderTexture2D *)JS_GetOpaque2(ctx, argv[0], js_RenderTexture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (RenderTexture2D *)JS_GetOpaque2(ctx, argv[0], js_RenderTexture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        RenderTexture2D arg0 = *argptr0;

    UnloadRenderTexture(arg0);


    return JS_UNDEFINED;
}

static JSValue js_UpdateTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
size_t data_size1;
    const void * arg1 = (const void *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);

    UpdateTexture(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_UpdateTextureRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;
size_t data_size2;
    const void * arg2 = (const void *)JS_GetArrayBuffer(ctx, &data_size2, argv[2]);

    UpdateTextureRec(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_SetTextureFilter(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetTextureFilter(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetTextureWrap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    SetTextureWrap(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawTexture(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawTexture(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawTextureV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawTextureV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawTextureEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawTextureEx(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawTextureRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawTextureRec(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawTexturePro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    Rectangle * argptr1 = (Rectangle *)JS_GetOpaque2(ctx, argv[1], js_Rectangle_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg1 = *argptr1;
    Rectangle * argptr2 = (Rectangle *)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawTexturePro(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawTextureNPatch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Texture2D * argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture2D_class_id);
        if (argptr0 == NULL)
        argptr0 = (Texture2D *)JS_GetOpaque2(ctx, argv[0], js_Texture_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg0 = *argptr0;
    NPatchInfo * argptr1 = (NPatchInfo *)JS_GetOpaque2(ctx, argv[1], js_NPatchInfo_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        NPatchInfo arg1 = *argptr1;
    Rectangle * argptr2 = (Rectangle *)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawTextureNPatch(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_Fade(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Color returnVal = Fade(arg0, arg1);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorToInt(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;

    int ret = ColorToInt(arg0);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_ColorNormalize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;

    Vector4 returnVal = ColorNormalize(arg0);


    
    Vector4* ret_ptr = (Vector4 *)js_malloc(ctx, sizeof(Vector4));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector4_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorFromNormalized(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector4 * argptr0 = (Vector4 *)JS_GetOpaque2(ctx, argv[0], js_Vector4_class_id);
        if (argptr0 == NULL)
        argptr0 = (Vector4 *)JS_GetOpaque2(ctx, argv[0], js_Quaternion_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector4 arg0 = *argptr0;

    Color returnVal = ColorFromNormalized(arg0);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorToHSV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;

    Vector3 returnVal = ColorToHSV(arg0);


    
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorFromHSV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    Color returnVal = ColorFromHSV(arg0, arg1, arg2);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorTint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;

    Color returnVal = ColorTint(arg0, arg1);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorBrightness(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Color returnVal = ColorBrightness(arg0, arg1);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorContrast(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Color returnVal = ColorContrast(arg0, arg1);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorAlpha(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Color returnVal = ColorAlpha(arg0, arg1);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_ColorAlphaBlend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Color * argptr0 = (Color *)JS_GetOpaque2(ctx, argv[0], js_Color_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Color arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    Color returnVal = ColorAlphaBlend(arg0, arg1, arg2);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);

    Color returnVal = GetColor(arg0);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetPixelColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    void * arg0 = (void *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    Color returnVal = GetPixelColor(arg0, arg1);


    
    Color* ret_ptr = (Color *)js_malloc(ctx, sizeof(Color));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Color_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_SetPixelColor(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
size_t data_size0;
    void * arg0 = (void *)JS_GetArrayBuffer(ctx, &data_size0, argv[0]);
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    SetPixelColor(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_GetPixelDataSize(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    int ret = GetPixelDataSize(arg0, arg1, arg2);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetFontDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Font returnVal = GetFontDefault();


    
    Font* ret_ptr = (Font *)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadFont(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Font returnVal = LoadFont(arg0);

    JS_FreeCString(ctx, arg0);

    
    Font* ret_ptr = (Font *)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadFontEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "codepoints");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                        int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    Font returnVal = LoadFontEx(arg0, arg1, arg2, arg3);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[2], "codepoints", JS_NewInt32(ctx, arg2_int));

    
    Font* ret_ptr = (Font *)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadFontFromImage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Font returnVal = LoadFontFromImage(arg0, arg1, arg2);


    
    Font* ret_ptr = (Font *)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadFontFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
size_t data_size1;
    const unsigned char * arg1 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
JSValue arg4_js = JS_GetPropertyStr(ctx, argv[4], "codepoints");
    int arg4_int;
    JS_ToInt32(ctx, &arg4_int, arg4_js);
    int * arg4 = &arg4_int;
                        int arg5;
    JS_ToInt32(ctx, &arg5, argv[5]);

    Font returnVal = LoadFontFromMemory(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[4], "codepoints", JS_NewInt32(ctx, arg4_int));

    
    Font* ret_ptr = (Font *)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsFontReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;

    bool ret = IsFontReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadFont(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;

    UnloadFont(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ExportFontAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportFontAsCode(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_DrawFPS(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    DrawFPS(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawText(arg0, arg1, arg2, arg3, arg4);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_DrawTextEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawTextEx(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg1);

    return JS_UNDEFINED;
}

static JSValue js_DrawTextPro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    double arg5;
    JS_ToFloat64(ctx, &arg5, argv[5]);
    double arg6;
    JS_ToFloat64(ctx, &arg6, argv[6]);
    Color * argptr7 = (Color *)JS_GetOpaque2(ctx, argv[7], js_Color_class_id);
        if (argptr7 == NULL) return JS_EXCEPTION;
                    
        Color arg7 = *argptr7;

    DrawTextPro(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    JS_FreeCString(ctx, arg1);

    return JS_UNDEFINED;
}

static JSValue js_DrawTextCodepoint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    Vector2 * argptr2 = (Vector2 *)JS_GetOpaque2(ctx, argv[2], js_Vector2_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawTextCodepoint(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawTextCodepoints(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "codepoints");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                        int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    Vector2 * argptr3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg3 = *argptr3;
    double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    double arg5;
    JS_ToFloat64(ctx, &arg5, argv[5]);
    Color * argptr6 = (Color *)JS_GetOpaque2(ctx, argv[6], js_Color_class_id);
        if (argptr6 == NULL) return JS_EXCEPTION;
                    
        Color arg6 = *argptr6;

    DrawTextCodepoints(arg0, arg1, arg2, arg3, arg4, arg5, arg6);

JS_SetPropertyStr(ctx, argv[1], "codepoints", JS_NewInt32(ctx, arg1_int));

    return JS_UNDEFINED;
}

static JSValue js_SetTextLineSpacing(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetTextLineSpacing(arg0);


    return JS_UNDEFINED;
}

static JSValue js_MeasureText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    int ret = MeasureText(arg0, arg1);

    JS_FreeCString(ctx, arg0);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_MeasureTextEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);

    Vector2 returnVal = MeasureTextEx(arg0, arg1, arg2, arg3);

    JS_FreeCString(ctx, arg1);

    
    Vector2* ret_ptr = (Vector2 *)js_malloc(ctx, sizeof(Vector2));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector2_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetGlyphIndex(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    int ret = GetGlyphIndex(arg0, arg1);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetGlyphInfo(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    GlyphInfo returnVal = GetGlyphInfo(arg0, arg1);


    
    GlyphInfo* ret_ptr = (GlyphInfo *)js_malloc(ctx, sizeof(GlyphInfo));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_GlyphInfo_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetGlyphAtlasRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    Rectangle returnVal = GetGlyphAtlasRec(arg0, arg1);


    
    Rectangle* ret_ptr = (Rectangle *)js_malloc(ctx, sizeof(Rectangle));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Rectangle_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadUTF8(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "codepoints");
    int arg0_int;
    JS_ToInt32(ctx, &arg0_int, arg0_js);
    int * arg0 = &arg0_int;
                        int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    char * retVal = LoadUTF8(arg0, arg1);

JS_SetPropertyStr(ctx, argv[0], "codepoints", JS_NewInt32(ctx, arg0_int));

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
   return ret;
}

static JSValue js_UnloadUTF8(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "text");
    size_t arg0_len;
    const char * arg0_str = JS_ToCStringLen(ctx, &arg0_len, arg0_js);
    char * arg0 = malloc(arg0_len+1);
    memcpy((void *)arg0, arg0_str, arg0_len);
    arg0[arg0_len] = 0;
                
    UnloadUTF8(arg0);

    JS_FreeCString(ctx, arg0_str);
                JS_SetPropertyStr(ctx, argv[0], "text", JS_NewString(ctx, arg0));
                free(arg0);

    return JS_UNDEFINED;
}

static JSValue js_LoadCodepoints(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "count");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    int * retBuf = LoadCodepoints(arg0, arg1);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[1], "count", JS_NewInt32(ctx, arg1_int));

    JSValue ret = JS_NewArray(ctx);
    for(int i; i < 7777 /*<<size>>*/; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewInt32(ctx, retBuf[i]));
    }
        return ret;
        
}

static JSValue js_UnloadCodepoints(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "codepoints");
    int arg0_int;
    JS_ToInt32(ctx, &arg0_int, arg0_js);
    int * arg0 = &arg0_int;
                    
    UnloadCodepoints(arg0);

JS_SetPropertyStr(ctx, argv[0], "codepoints", JS_NewInt32(ctx, arg0_int));

    return JS_UNDEFINED;
}

static JSValue js_GetCodepointCount(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    int ret = GetCodepointCount(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetCodepoint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "codepointSize");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    int ret = GetCodepoint(arg0, arg1);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[1], "codepointSize", JS_NewInt32(ctx, arg1_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetCodepointNext(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "codepointSize");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    int ret = GetCodepointNext(arg0, arg1);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[1], "codepointSize", JS_NewInt32(ctx, arg1_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GetCodepointPrevious(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "codepointSize");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    int ret = GetCodepointPrevious(arg0, arg1);

    JS_FreeCString(ctx, arg0);
JS_SetPropertyStr(ctx, argv[1], "codepointSize", JS_NewInt32(ctx, arg1_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_CodepointToUTF8(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "utf8Size");
    int arg1_int;
    JS_ToInt32(ctx, &arg1_int, arg1_js);
    int * arg1 = &arg1_int;
                    
    const char * returnVal = CodepointToUTF8(arg0, arg1);

JS_SetPropertyStr(ctx, argv[1], "utf8Size", JS_NewInt32(ctx, arg1_int));

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextCopy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "dst");
    size_t arg0_len;
    const char * arg0_str = JS_ToCStringLen(ctx, &arg0_len, arg0_js);
    char * arg0 = malloc(arg0_len+1);
    memcpy((void *)arg0, arg0_str, arg0_len);
    arg0[arg0_len] = 0;
                    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = TextCopy(arg0, arg1);

    JS_FreeCString(ctx, arg0_str);
                JS_SetPropertyStr(ctx, argv[0], "dst", JS_NewString(ctx, arg0));
                free(arg0);
    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_TextIsEqual(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = TextIsEqual(arg0, arg1);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_TextLength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    unsigned int ret = TextLength(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewUint32(ctx, ret);
}

static JSValue js_TextSubtext(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    const char * returnVal = TextSubtext(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextReplace(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "text");
    size_t arg0_len;
    const char * arg0_str = JS_ToCStringLen(ctx, &arg0_len, arg0_js);
    char * arg0 = malloc(arg0_len+1);
    memcpy((void *)arg0, arg0_str, arg0_len);
    arg0[arg0_len] = 0;
                    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);

    char * retVal = TextReplace(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0_str);
                JS_SetPropertyStr(ctx, argv[0], "text", JS_NewString(ctx, arg0));
                free(arg0);
    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2);

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
   return ret;
}

static JSValue js_TextInsert(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    char * retVal = TextInsert(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);
   return ret;
}

static JSValue js_TextAppend(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    JSValue arg0_js = JS_GetPropertyStr(ctx, argv[0], "text");
    size_t arg0_len;
    const char * arg0_str = JS_ToCStringLen(ctx, &arg0_len, arg0_js);
    char * arg0 = malloc(arg0_len+1);
    memcpy((void *)arg0, arg0_str, arg0_len);
    arg0[arg0_len] = 0;
                    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "position");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    TextAppend(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0_str);
                JS_SetPropertyStr(ctx, argv[0], "text", JS_NewString(ctx, arg0));
                free(arg0);
    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "position", JS_NewInt32(ctx, arg2_int));

    return JS_UNDEFINED;
}

static JSValue js_TextFindIndex(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = TextFindIndex(arg0, arg1);

    JS_FreeCString(ctx, arg0);
    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_TextToUpper(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = TextToUpper(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToLower(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = TextToLower(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToPascal(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    const char * returnVal = TextToPascal(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_TextToInteger(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    int ret = TextToInteger(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_DrawLine3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawLine3D(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawPoint3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;

    DrawPoint3D(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawCircle3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawCircle3D(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawTriangle3D(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawTriangle3D(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawCube(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawCube(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawCubeV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawCubeV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawCubeWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawCubeWires(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawCubeWiresV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawCubeWiresV(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawSphere(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawSphereEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawSphereEx(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawSphereWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawSphereWires(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawCylinder(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCylinder(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCylinderEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCylinderEx(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCylinderWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCylinderWires(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCylinderWiresEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCylinderWiresEx(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCapsule(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCapsule(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawCapsuleWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawCapsuleWires(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawPlane(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    Vector2 * argptr1 = (Vector2 *)JS_GetOpaque2(ctx, argv[1], js_Vector2_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg1 = *argptr1;
    Color * argptr2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Color arg2 = *argptr2;

    DrawPlane(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_DrawRay(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Ray * argptr0 = (Ray *)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Ray arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;

    DrawRay(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawGrid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    DrawGrid(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_LoadModel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Model returnVal = LoadModel(arg0);

    JS_FreeCString(ctx, arg0);

    
    Model* ret_ptr = (Model *)js_malloc(ctx, sizeof(Model));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Model_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadModelFromMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Mesh * argptr0 = (Mesh *)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Mesh arg0 = *argptr0;

    Model returnVal = LoadModelFromMesh(arg0);


    
    Model* ret_ptr = (Model *)js_malloc(ctx, sizeof(Model));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Model_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsModelReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;

    bool ret = IsModelReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadModel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;

    UnloadModel(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetModelBoundingBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;

    BoundingBox returnVal = GetModelBoundingBox(arg0);


    
    BoundingBox* ret_ptr = (BoundingBox *)js_malloc(ctx, sizeof(BoundingBox));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_DrawModel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawModel(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawModelEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Vector3 * argptr4 = (Vector3 *)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg4 = *argptr4;
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawModelEx(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawModelWires(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    Color * argptr3 = (Color *)JS_GetOpaque2(ctx, argv[3], js_Color_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Color arg3 = *argptr3;

    DrawModelWires(arg0, arg1, arg2, arg3);


    return JS_UNDEFINED;
}

static JSValue js_DrawModelWiresEx(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Vector3 * argptr4 = (Vector3 *)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg4 = *argptr4;
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawModelWiresEx(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawBoundingBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    BoundingBox * argptr0 = (BoundingBox *)JS_GetOpaque2(ctx, argv[0], js_BoundingBox_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        BoundingBox arg0 = *argptr0;
    Color * argptr1 = (Color *)JS_GetOpaque2(ctx, argv[1], js_Color_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Color arg1 = *argptr1;

    DrawBoundingBox(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_DrawBillboard(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (argptr0 == NULL)
        argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera arg0 = *argptr0;
    Texture2D * argptr1 = (Texture2D *)JS_GetOpaque2(ctx, argv[1], js_Texture2D_class_id);
        if (argptr1 == NULL)
        argptr1 = (Texture2D *)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    DrawBillboard(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_DrawBillboardRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (argptr0 == NULL)
        argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera arg0 = *argptr0;
    Texture2D * argptr1 = (Texture2D *)JS_GetOpaque2(ctx, argv[1], js_Texture2D_class_id);
        if (argptr1 == NULL)
        argptr1 = (Texture2D *)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg1 = *argptr1;
    Rectangle * argptr2 = (Rectangle *)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg2 = *argptr2;
    Vector3 * argptr3 = (Vector3 *)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg3 = *argptr3;
    Vector2 * argptr4 = (Vector2 *)JS_GetOpaque2(ctx, argv[4], js_Vector2_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg4 = *argptr4;
    Color * argptr5 = (Color *)JS_GetOpaque2(ctx, argv[5], js_Color_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Color arg5 = *argptr5;

    DrawBillboardRec(arg0, arg1, arg2, arg3, arg4, arg5);


    return JS_UNDEFINED;
}

static JSValue js_DrawBillboardPro(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (argptr0 == NULL)
        argptr0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Camera arg0 = *argptr0;
    Texture2D * argptr1 = (Texture2D *)JS_GetOpaque2(ctx, argv[1], js_Texture2D_class_id);
        if (argptr1 == NULL)
        argptr1 = (Texture2D *)JS_GetOpaque2(ctx, argv[1], js_Texture_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Texture2D arg1 = *argptr1;
    Rectangle * argptr2 = (Rectangle *)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg2 = *argptr2;
    Vector3 * argptr3 = (Vector3 *)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg3 = *argptr3;
    Vector3 * argptr4 = (Vector3 *)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg4 = *argptr4;
    Vector2 * argptr5 = (Vector2 *)JS_GetOpaque2(ctx, argv[5], js_Vector2_class_id);
        if (argptr5 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg5 = *argptr5;
    Vector2 * argptr6 = (Vector2 *)JS_GetOpaque2(ctx, argv[6], js_Vector2_class_id);
        if (argptr6 == NULL) return JS_EXCEPTION;
                    
        Vector2 arg6 = *argptr6;
    double arg7;
    JS_ToFloat64(ctx, &arg7, argv[7]);
    Color * argptr8 = (Color *)JS_GetOpaque2(ctx, argv[8], js_Color_class_id);
        if (argptr8 == NULL) return JS_EXCEPTION;
                    
        Color arg8 = *argptr8;

    DrawBillboardPro(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);


    return JS_UNDEFINED;
}

static JSValue js_UpdateMeshBuffer(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Mesh * argptr0 = (Mesh *)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Mesh arg0 = *argptr0;
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
size_t data_size2;
    const void * arg2 = (const void *)JS_GetArrayBuffer(ctx, &data_size2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);

    UpdateMeshBuffer(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_UnloadMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Mesh * argptr0 = (Mesh *)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Mesh arg0 = *argptr0;

    UnloadMesh(arg0);


    return JS_UNDEFINED;
}

static JSValue js_DrawMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Mesh * argptr0 = (Mesh *)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Mesh arg0 = *argptr0;
    Material * argptr1 = (Material *)JS_GetOpaque2(ctx, argv[1], js_Material_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Material arg1 = *argptr1;
    Matrix * argptr2 = (Matrix *)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Matrix arg2 = *argptr2;

    DrawMesh(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_ExportMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Mesh * argptr0 = (Mesh *)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Mesh arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportMesh(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_GetMeshBoundingBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Mesh * argptr0 = (Mesh *)JS_GetOpaque2(ctx, argv[0], js_Mesh_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Mesh arg0 = *argptr0;

    BoundingBox returnVal = GetMeshBoundingBox(arg0);


    
    BoundingBox* ret_ptr = (BoundingBox *)js_malloc(ctx, sizeof(BoundingBox));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_BoundingBox_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshPoly(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Mesh returnVal = GenMeshPoly(arg0, arg1);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshPlane(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    Mesh returnVal = GenMeshPlane(arg0, arg1, arg2, arg3);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshCube(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    Mesh returnVal = GenMeshCube(arg0, arg1, arg2);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Mesh returnVal = GenMeshSphere(arg0, arg1, arg2);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshHemiSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Mesh returnVal = GenMeshHemiSphere(arg0, arg1, arg2);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshCylinder(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Mesh returnVal = GenMeshCylinder(arg0, arg1, arg2);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshCone(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Mesh returnVal = GenMeshCone(arg0, arg1, arg2);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshTorus(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    Mesh returnVal = GenMeshTorus(arg0, arg1, arg2, arg3);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshKnot(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);

    Mesh returnVal = GenMeshKnot(arg0, arg1, arg2, arg3);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshHeightmap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;

    Mesh returnVal = GenMeshHeightmap(arg0, arg1);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GenMeshCubicmap(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Image * argptr0 = (Image *)JS_GetOpaque2(ctx, argv[0], js_Image_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Image arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;

    Mesh returnVal = GenMeshCubicmap(arg0, arg1);


    
    Mesh* ret_ptr = (Mesh *)js_malloc(ctx, sizeof(Mesh));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Mesh_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadMaterialDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Material returnVal = LoadMaterialDefault();


    
    Material* ret_ptr = (Material *)js_malloc(ctx, sizeof(Material));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Material_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsMaterialReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Material * argptr0 = (Material *)JS_GetOpaque2(ctx, argv[0], js_Material_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Material arg0 = *argptr0;

    bool ret = IsMaterialReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadMaterial(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Material * argptr0 = (Material *)JS_GetOpaque2(ctx, argv[0], js_Material_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Material arg0 = *argptr0;

    UnloadMaterial(arg0);


    return JS_UNDEFINED;
}

static JSValue js_UpdateModelAnimation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;
    ModelAnimation * argptr1 = (ModelAnimation *)JS_GetOpaque2(ctx, argv[1], js_ModelAnimation_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        ModelAnimation arg1 = *argptr1;
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    UpdateModelAnimation(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_UnloadModelAnimation(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    ModelAnimation * argptr0 = (ModelAnimation *)JS_GetOpaque2(ctx, argv[0], js_ModelAnimation_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        ModelAnimation arg0 = *argptr0;

    UnloadModelAnimation(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsModelAnimationValid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Model * argptr0 = (Model *)JS_GetOpaque2(ctx, argv[0], js_Model_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Model arg0 = *argptr0;
    ModelAnimation * argptr1 = (ModelAnimation *)JS_GetOpaque2(ctx, argv[1], js_ModelAnimation_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        ModelAnimation arg1 = *argptr1;

    bool ret = IsModelAnimationValid(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionSpheres(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Vector3 * argptr0 = (Vector3 *)JS_GetOpaque2(ctx, argv[0], js_Vector3_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    double arg3;
    JS_ToFloat64(ctx, &arg3, argv[3]);

    bool ret = CheckCollisionSpheres(arg0, arg1, arg2, arg3);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionBoxes(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    BoundingBox * argptr0 = (BoundingBox *)JS_GetOpaque2(ctx, argv[0], js_BoundingBox_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        BoundingBox arg0 = *argptr0;
    BoundingBox * argptr1 = (BoundingBox *)JS_GetOpaque2(ctx, argv[1], js_BoundingBox_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        BoundingBox arg1 = *argptr1;

    bool ret = CheckCollisionBoxes(arg0, arg1);


    return JS_NewBool(ctx, ret);
}

static JSValue js_CheckCollisionBoxSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    BoundingBox * argptr0 = (BoundingBox *)JS_GetOpaque2(ctx, argv[0], js_BoundingBox_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        BoundingBox arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    bool ret = CheckCollisionBoxSphere(arg0, arg1, arg2);


    return JS_NewBool(ctx, ret);
}

static JSValue js_GetRayCollisionSphere(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Ray * argptr0 = (Ray *)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Ray arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);

    RayCollision returnVal = GetRayCollisionSphere(arg0, arg1, arg2);


    
    RayCollision* ret_ptr = (RayCollision *)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetRayCollisionBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Ray * argptr0 = (Ray *)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Ray arg0 = *argptr0;
    BoundingBox * argptr1 = (BoundingBox *)JS_GetOpaque2(ctx, argv[1], js_BoundingBox_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        BoundingBox arg1 = *argptr1;

    RayCollision returnVal = GetRayCollisionBox(arg0, arg1);


    
    RayCollision* ret_ptr = (RayCollision *)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetRayCollisionMesh(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Ray * argptr0 = (Ray *)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Ray arg0 = *argptr0;
    Mesh * argptr1 = (Mesh *)JS_GetOpaque2(ctx, argv[1], js_Mesh_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Mesh arg1 = *argptr1;
    Matrix * argptr2 = (Matrix *)JS_GetOpaque2(ctx, argv[2], js_Matrix_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Matrix arg2 = *argptr2;

    RayCollision returnVal = GetRayCollisionMesh(arg0, arg1, arg2);


    
    RayCollision* ret_ptr = (RayCollision *)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetRayCollisionTriangle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Ray * argptr0 = (Ray *)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Ray arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    Vector3 * argptr3 = (Vector3 *)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg3 = *argptr3;

    RayCollision returnVal = GetRayCollisionTriangle(arg0, arg1, arg2, arg3);


    
    RayCollision* ret_ptr = (RayCollision *)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetRayCollisionQuad(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Ray * argptr0 = (Ray *)JS_GetOpaque2(ctx, argv[0], js_Ray_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Ray arg0 = *argptr0;
    Vector3 * argptr1 = (Vector3 *)JS_GetOpaque2(ctx, argv[1], js_Vector3_class_id);
        if (argptr1 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg1 = *argptr1;
    Vector3 * argptr2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg2 = *argptr2;
    Vector3 * argptr3 = (Vector3 *)JS_GetOpaque2(ctx, argv[3], js_Vector3_class_id);
        if (argptr3 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg3 = *argptr3;
    Vector3 * argptr4 = (Vector3 *)JS_GetOpaque2(ctx, argv[4], js_Vector3_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Vector3 arg4 = *argptr4;

    RayCollision returnVal = GetRayCollisionQuad(arg0, arg1, arg2, arg3, arg4);


    
    RayCollision* ret_ptr = (RayCollision *)js_malloc(ctx, sizeof(RayCollision));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_RayCollision_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_InitAudioDevice(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    InitAudioDevice();


    return JS_UNDEFINED;
}

static JSValue js_CloseAudioDevice(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    CloseAudioDevice();


    return JS_UNDEFINED;
}

static JSValue js_IsAudioDeviceReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = IsAudioDeviceReady();


    return JS_NewBool(ctx, ret);
}

static JSValue js_SetMasterVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);

    SetMasterVolume(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetMasterVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    float ret = GetMasterVolume();


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_LoadWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Wave returnVal = LoadWave(arg0);

    JS_FreeCString(ctx, arg0);

    
    Wave* ret_ptr = (Wave *)js_malloc(ctx, sizeof(Wave));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadWaveFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
size_t data_size1;
    const unsigned char * arg1 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Wave returnVal = LoadWaveFromMemory(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);

    
    Wave* ret_ptr = (Wave *)js_malloc(ctx, sizeof(Wave));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsWaveReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;

    bool ret = IsWaveReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_LoadSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Sound returnVal = LoadSound(arg0);

    JS_FreeCString(ctx, arg0);

    
    Sound* ret_ptr = (Sound *)js_malloc(ctx, sizeof(Sound));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadSoundFromWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;

    Sound returnVal = LoadSoundFromWave(arg0);


    
    Sound* ret_ptr = (Sound *)js_malloc(ctx, sizeof(Sound));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadSoundAlias(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    Sound returnVal = LoadSoundAlias(arg0);


    
    Sound* ret_ptr = (Sound *)js_malloc(ctx, sizeof(Sound));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Sound_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsSoundReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    bool ret = IsSoundReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UpdateSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;
size_t data_size1;
    const void * arg1 = (const void *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    UpdateSound(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_UnloadWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;

    UnloadWave(arg0);


    return JS_UNDEFINED;
}

static JSValue js_UnloadSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    UnloadSound(arg0);


    return JS_UNDEFINED;
}

static JSValue js_UnloadSoundAlias(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    UnloadSoundAlias(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ExportWave(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportWave(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_ExportWaveAsCode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    bool ret = ExportWaveAsCode(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewBool(ctx, ret);
}

static JSValue js_PlaySound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    PlaySound(arg0);


    return JS_UNDEFINED;
}

static JSValue js_StopSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    StopSound(arg0);


    return JS_UNDEFINED;
}

static JSValue js_PauseSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    PauseSound(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ResumeSound(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    ResumeSound(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsSoundPlaying(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;

    bool ret = IsSoundPlaying(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_SetSoundVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetSoundVolume(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetSoundPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetSoundPitch(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetSoundPan(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Sound * argptr0 = (Sound *)JS_GetOpaque2(ctx, argv[0], js_Sound_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Sound arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetSoundPan(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_WaveCopy(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;

    Wave returnVal = WaveCopy(arg0);


    
    Wave* ret_ptr = (Wave *)js_malloc(ctx, sizeof(Wave));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Wave_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadWaveSamples(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Wave * argptr0 = (Wave *)JS_GetOpaque2(ctx, argv[0], js_Wave_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Wave arg0 = *argptr0;

    float * retBuf = LoadWaveSamples(arg0);


    JSValue ret = JS_NewArray(ctx);
            //TODO
            return ret;
        
}

static JSValue js_LoadMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    Music returnVal = LoadMusicStream(arg0);

    JS_FreeCString(ctx, arg0);

    
    Music* ret_ptr = (Music *)js_malloc(ctx, sizeof(Music));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Music_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_LoadMusicStreamFromMemory(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
size_t data_size1;
    const unsigned char * arg1 = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    Music returnVal = LoadMusicStreamFromMemory(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg0);

    
    Music* ret_ptr = (Music *)js_malloc(ctx, sizeof(Music));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Music_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsMusicReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    bool ret = IsMusicReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    UnloadMusicStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_PlayMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    PlayMusicStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsMusicStreamPlaying(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    bool ret = IsMusicStreamPlaying(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UpdateMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    UpdateMusicStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_StopMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    StopMusicStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_PauseMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    PauseMusicStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ResumeMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    ResumeMusicStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SeekMusicStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SeekMusicStream(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetMusicVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetMusicVolume(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetMusicPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetMusicPitch(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetMusicPan(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetMusicPan(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_GetMusicTimeLength(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    float ret = GetMusicTimeLength(arg0);


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_GetMusicTimePlayed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Music * argptr0 = (Music *)JS_GetOpaque2(ctx, argv[0], js_Music_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Music arg0 = *argptr0;

    float ret = GetMusicTimePlayed(arg0);


    return JS_NewFloat64(ctx, ret);
}

static JSValue js_LoadAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    unsigned int arg0;
    JS_ToUint32(ctx, &arg0, argv[0]);
    unsigned int arg1;
    JS_ToUint32(ctx, &arg1, argv[1]);
    unsigned int arg2;
    JS_ToUint32(ctx, &arg2, argv[2]);

    AudioStream returnVal = LoadAudioStream(arg0, arg1, arg2);


    
    AudioStream* ret_ptr = (AudioStream *)js_malloc(ctx, sizeof(AudioStream));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_AudioStream_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_IsAudioStreamReady(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    bool ret = IsAudioStreamReady(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_UnloadAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    UnloadAudioStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_UpdateAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;
size_t data_size1;
    const void * arg1 = (const void *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    UpdateAudioStream(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_IsAudioStreamProcessed(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    bool ret = IsAudioStreamProcessed(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_PlayAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    PlayAudioStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_PauseAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    PauseAudioStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_ResumeAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    ResumeAudioStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_IsAudioStreamPlaying(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    bool ret = IsAudioStreamPlaying(arg0);


    return JS_NewBool(ctx, ret);
}

static JSValue js_StopAudioStream(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;

    StopAudioStream(arg0);


    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamVolume(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetAudioStreamVolume(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetAudioStreamPitch(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamPan(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    AudioStream * argptr0 = (AudioStream *)JS_GetOpaque2(ctx, argv[0], js_AudioStream_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        AudioStream arg0 = *argptr0;
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    SetAudioStreamPan(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_SetAudioStreamBufferSizeDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    SetAudioStreamBufferSizeDefault(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GetCameraForward(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);

    Vector3 returnVal = GetCameraForward(arg0);


    
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetCameraUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);

    Vector3 returnVal = GetCameraUp(arg0);


    
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetCameraRight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);

    Vector3 returnVal = GetCameraRight(arg0);


    
    Vector3* ret_ptr = (Vector3 *)js_malloc(ctx, sizeof(Vector3));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Vector3_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_CameraMoveForward(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    JS_BOOL argbool2 = JS_ToBool(ctx, argv[2]);
    bool arg2 = (bool) argbool2;

    CameraMoveForward(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_CameraMoveUp(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    CameraMoveUp(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_CameraMoveRight(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    JS_BOOL argbool2 = JS_ToBool(ctx, argv[2]);
    bool arg2 = (bool) argbool2;

    CameraMoveRight(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_CameraMoveToTarget(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    CameraMoveToTarget(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_CameraYaw(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    JS_BOOL argbool2 = JS_ToBool(ctx, argv[2]);
    bool arg2 = (bool) argbool2;

    CameraYaw(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_CameraPitch(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);
    JS_BOOL argbool2 = JS_ToBool(ctx, argv[2]);
    bool arg2 = (bool) argbool2;
    JS_BOOL argbool3 = JS_ToBool(ctx, argv[3]);
    bool arg3 = (bool) argbool3;
    JS_BOOL argbool4 = JS_ToBool(ctx, argv[4]);
    bool arg4 = (bool) argbool4;

    CameraPitch(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_CameraRoll(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    CameraRoll(arg0, arg1);


    return JS_UNDEFINED;
}

static JSValue js_GetCameraViewMatrix(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);

    Matrix returnVal = GetCameraViewMatrix(arg0);


    
    Matrix* ret_ptr = (Matrix *)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GetCameraProjectionMatrix(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Camera * arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera_class_id);
        if (arg0 == NULL)
        arg0 = (Camera *)JS_GetOpaque2(ctx, argv[0], js_Camera3D_class_id);
    double arg1;
    JS_ToFloat64(ctx, &arg1, argv[1]);

    Matrix returnVal = GetCameraProjectionMatrix(arg0, arg1);


    
    Matrix* ret_ptr = (Matrix *)js_malloc(ctx, sizeof(Matrix));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Matrix_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}



static JSClassID js_GuiStyleProp_class_id;

static JSValue js_GuiStyleProp_get(JSContext *ctx, JSValueConst this_val, int magic)
{
    GuiStyleProp *s = JS_GetOpaque2(ctx, this_val, js_GuiStyleProp_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    return JS_NewUint32(ctx, (unsigned short) s->controlId);
}

if (magic == 1) {
    return JS_NewUint32(ctx, (unsigned short) s->propertyId);
}

if (magic == 2) {
    return JS_NewInt32(ctx, (int) s->propertyValue);
}


    return JS_UNDEFINED;
}

static JSValue js_GuiStyleProp_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    GuiStyleProp *s = JS_GetOpaque2(ctx, this_val, js_GuiStyleProp_class_id);
    if (!s)
        return JS_EXCEPTION;

    
if (magic == 0) {
    unsigned short v0;
    if (JS_ToUint32(ctx, &v0, val))
        return JS_EXCEPTION;
    s->controlId = (unsigned short) v0;
}

if (magic == 1) {
    unsigned short v1;
    if (JS_ToUint32(ctx, &v1, val))
        return JS_EXCEPTION;
    s->propertyId = (unsigned short) v1;
}

if (magic == 2) {
    int v2;
    if (JS_ToInt32(ctx, &v2, val))
        return JS_EXCEPTION;
    s->propertyValue = (int) v2;
}

    
    return JS_UNDEFINED;
}

static void js_GuiStyleProp_finalizer(JSRuntime *rt, JSValue val)
{
    GuiStyleProp *s = JS_GetOpaque(val, js_GuiStyleProp_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}

static JSValue js_GuiStyleProp_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_GuiStyleProp_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }*/
    
    GuiStyleProp *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    
unsigned short v0;
if (JS_ToUint32(ctx, &v0, argv[0]))
        goto fail;
s->controlId = (unsigned short) v0;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 0 = %lf", s->0);*/
        

unsigned short v1;
if (JS_ToUint32(ctx, &v1, argv[1]))
        goto fail;
s->propertyId = (unsigned short) v1;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 1 = %lf", s->1);*/
        

int v2;
if (JS_ToInt32(ctx, &v2, argv[2]))
        goto fail;
s->propertyValue = (int) v2;

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: 2 = %lf", s->2);*/
        

    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_GuiStyleProp_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static JSClassDef js_GuiStyleProp_class = {
    "GuiStyleProp",
    .finalizer = js_GuiStyleProp_finalizer,
};

static const JSCFunctionListEntry js_GuiStyleProp_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("controlId", js_GuiStyleProp_get, js_GuiStyleProp_set, 0),
    JS_CGETSET_MAGIC_DEF("propertyId", js_GuiStyleProp_get, js_GuiStyleProp_set, 1),
    JS_CGETSET_MAGIC_DEF("propertyValue", js_GuiStyleProp_get, js_GuiStyleProp_set, 2),

    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GuiStyleProp", JS_PROP_CONFIGURABLE ),*/
};
    
static int js_declare_GuiStyleProp(JSContext *ctx, JSModuleDef *m)
{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_GuiStyleProp_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_GuiStyleProp_class_id, &js_GuiStyleProp_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_GuiStyleProp_proto_funcs, countof(js_GuiStyleProp_proto_funcs));

    class = JS_NewCFunction2(ctx, js_GuiStyleProp_ctor, "GuiStyleProp", 3, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_GuiStyleProp_class_id, proto);

    JS_SetModuleExport(ctx, m, "GuiStyleProp", class);
    return 0;
}

static JSValue js_GuiEnable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiEnable();


    return JS_UNDEFINED;
}

static JSValue js_GuiDisable(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiDisable();


    return JS_UNDEFINED;
}

static JSValue js_GuiLock(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiLock();


    return JS_UNDEFINED;
}

static JSValue js_GuiUnlock(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiUnlock();


    return JS_UNDEFINED;
}

static JSValue js_GuiIsLocked(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    bool ret = GuiIsLocked();


    return JS_NewBool(ctx, ret);
}

static JSValue js_GuiSetAlpha(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    double arg0;
    JS_ToFloat64(ctx, &arg0, argv[0]);

    GuiSetAlpha(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GuiSetState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    GuiSetState(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GuiGetState(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    int ret = GuiGetState();


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiSetFont(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Font * argptr0 = (Font *)JS_GetOpaque2(ctx, argv[0], js_Font_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Font arg0 = *argptr0;

    GuiSetFont(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GuiGetFont(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    Font returnVal = GuiGetFont();


    
    Font* ret_ptr = (Font *)js_malloc(ctx, sizeof(Font));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_Font_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    
}

static JSValue js_GuiSetStyle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    GuiSetStyle(arg0, arg1, arg2);


    return JS_UNDEFINED;
}

static JSValue js_GuiGetStyle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);

    int ret = GuiGetStyle(arg0, arg1);


    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiLoadStyle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    GuiLoadStyle(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_GuiLoadStyleDefault(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiLoadStyleDefault();


    return JS_UNDEFINED;
}

static JSValue js_GuiEnableTooltip(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiEnableTooltip();


    return JS_UNDEFINED;
}

static JSValue js_GuiDisableTooltip(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{

    GuiDisableTooltip();


    return JS_UNDEFINED;
}

static JSValue js_GuiSetTooltip(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    GuiSetTooltip(arg0);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_GuiIconText(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    const char * returnVal = GuiIconText(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    JSValue ret = JS_NewString(ctx, returnVal);
    return ret;
}

static JSValue js_GuiSetIconScale(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);

    GuiSetIconScale(arg0);


    return JS_UNDEFINED;
}

static JSValue js_GuiLoadIcons(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    JS_BOOL argbool1 = JS_ToBool(ctx, argv[1]);
    bool arg1 = (bool) argbool1;

    GuiLoadIcons(arg0, arg1);

    JS_FreeCString(ctx, arg0);

    return JS_UNDEFINED;
}

static JSValue js_GuiDrawIcon(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    int arg0;
    JS_ToInt32(ctx, &arg0, argv[0]);
    int arg1;
    JS_ToInt32(ctx, &arg1, argv[1]);
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Color * argptr4 = (Color *)JS_GetOpaque2(ctx, argv[4], js_Color_class_id);
        if (argptr4 == NULL) return JS_EXCEPTION;
                    
        Color arg4 = *argptr4;

    GuiDrawIcon(arg0, arg1, arg2, arg3, arg4);


    return JS_UNDEFINED;
}

static JSValue js_GuiWindowBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiWindowBox(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiGroupBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiGroupBox(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiLine(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiLine(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiPanel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiPanel(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiTabBar(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{


        Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;

	JSValue length_js = JS_GetProperty(ctx, argv[1], JS_ATOM_length);
	
	int32_t length;
	
        JS_ToInt32(ctx, &length, length_js);

	char ** tabs = (char **)malloc((length+1)*sizeof(char *));

	tabs[length] = 0;

	for (int i=0; i < length; ++i) {{

	  JSValue val = JS_GetPropertyUint32(ctx, argv[1], i);

	  const char * str = JS_ToCString(ctx, val);
	  
	  tabs[i] = str;
	}}
	
    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);

    JSValue arg3_js = JS_GetPropertyStr(ctx, argv[3], "active");
    int arg3;
    JS_ToInt32(ctx, &arg3, arg3_js);

    int ret = GuiTabBar(arg0, tabs, arg2, &arg3);

    JS_SetPropertyStr(ctx, argv[3], "active", JS_NewInt32(ctx, arg3));

    for (int i=0; i < length; ++i) {{

	  JS_FreeCString(ctx, tabs[i]);
    }}
        
    if (tabs)
        free(tabs);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiScrollPanel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Rectangle * argptr2 = (Rectangle *)JS_GetOpaque2(ctx, argv[2], js_Rectangle_class_id);
        if (argptr2 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg2 = *argptr2;
    Vector2 * arg3 = (Vector2 *)JS_GetOpaque2(ctx, argv[3], js_Vector2_class_id);
    Rectangle * arg4 = (Rectangle *)JS_GetOpaque2(ctx, argv[4], js_Rectangle_class_id);

    int ret = GuiScrollPanel(arg0, arg1, arg2, arg3, arg4);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiLabel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiLabel(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiButton(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiButton(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiLabelButton(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiLabelButton(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiToggle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "active");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    int ret = GuiToggle(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "active", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiToggleGroup(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "active");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    int ret = GuiToggleGroup(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "active", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiToggleSlider(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "active");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    int ret = GuiToggleSlider(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "active", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiCheckBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "checked");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    int ret = GuiCheckBox(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "checked", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiComboBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "active");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    
    int ret = GuiComboBox(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "active", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiDropdownBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "active");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                        JS_BOOL argbool3 = JS_ToBool(ctx, argv[3]);
    bool arg3 = (bool) argbool3;

    int ret = GuiDropdownBox(arg0, arg1, arg2, arg3);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "active", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiSpinner(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "value");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                        int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    JS_BOOL argbool5 = JS_ToBool(ctx, argv[5]);
    bool arg5 = (bool) argbool5;

    int ret = GuiSpinner(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "value", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiValueBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "value");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                        int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    int arg4;
    JS_ToInt32(ctx, &arg4, argv[4]);
    JS_BOOL argbool5 = JS_ToBool(ctx, argv[5]);
    bool arg5 = (bool) argbool5;

    int ret = GuiValueBox(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "value", JS_NewInt32(ctx, arg2_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiValueBoxFloat(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "textValue");
    size_t arg2_len;
    const char * arg2_str = JS_ToCStringLen(ctx, &arg2_len, arg2_js);
    char * arg2 = malloc(arg2_len+1);
    memcpy((void *)arg2, arg2_str, arg2_len);
    arg2[arg2_len] = 0;
                JSValue arg3_js = JS_GetPropertyStr(ctx, argv[3], "value");
    double arg3_double;
    JS_ToFloat64(ctx, &arg3_double, arg3_js);
    float  arg3_float = (float)arg3_double;
    float * arg3 = &arg3_float;
                        JS_BOOL argbool4 = JS_ToBool(ctx, argv[4]);
    bool arg4 = (bool) argbool4;

    int ret = GuiValueBoxFloat(arg0, arg1, arg2, arg3, arg4);

    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2_str);
                JS_SetPropertyStr(ctx, argv[2], "textValue", JS_NewString(ctx, arg2));
                free(arg2);
JS_SetPropertyStr(ctx, argv[3], "value", JS_NewFloat64(ctx, arg3_float));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiTextBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    JSValue arg1_js = JS_GetPropertyStr(ctx, argv[1], "text");
    size_t arg1_len;
    const char * arg1_str = JS_ToCStringLen(ctx, &arg1_len, arg1_js);
    char * arg1 = malloc(arg1_len+1);
    memcpy((void *)arg1, arg1_str, arg1_len);
    arg1[arg1_len] = 0;
                    int arg2;
    JS_ToInt32(ctx, &arg2, argv[2]);
    JS_BOOL argbool3 = JS_ToBool(ctx, argv[3]);
    bool arg3 = (bool) argbool3;

    int ret = GuiTextBox(arg0, arg1, arg2, arg3);

    JS_FreeCString(ctx, arg1_str);
                JS_SetPropertyStr(ctx, argv[1], "text", JS_NewString(ctx, arg1));
                free(arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiSlider(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);
JSValue arg3_js = JS_GetPropertyStr(ctx, argv[3], "value");
    double arg3_double;
    JS_ToFloat64(ctx, &arg3_double, arg3_js);
    float  arg3_float = (float)arg3_double;
    float * arg3 = &arg3_float;
                        double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    double arg5;
    JS_ToFloat64(ctx, &arg5, argv[5]);

    int ret = GuiSlider(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2);
JS_SetPropertyStr(ctx, argv[3], "value", JS_NewFloat64(ctx, arg3_float));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiSliderBar(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);
JSValue arg3_js = JS_GetPropertyStr(ctx, argv[3], "value");
    double arg3_double;
    JS_ToFloat64(ctx, &arg3_double, arg3_js);
    float  arg3_float = (float)arg3_double;
    float * arg3 = &arg3_float;
                        double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    double arg5;
    JS_ToFloat64(ctx, &arg5, argv[5]);

    int ret = GuiSliderBar(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2);
JS_SetPropertyStr(ctx, argv[3], "value", JS_NewFloat64(ctx, arg3_float));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiProgressBar(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);
JSValue arg3_js = JS_GetPropertyStr(ctx, argv[3], "value");
    double arg3_double;
    JS_ToFloat64(ctx, &arg3_double, arg3_js);
    float  arg3_float = (float)arg3_double;
    float * arg3 = &arg3_float;
                        double arg4;
    JS_ToFloat64(ctx, &arg4, argv[4]);
    double arg5;
    JS_ToFloat64(ctx, &arg5, argv[5]);

    int ret = GuiProgressBar(arg0, arg1, arg2, arg3, arg4, arg5);

    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2);
JS_SetPropertyStr(ctx, argv[3], "value", JS_NewFloat64(ctx, arg3_float));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiStatusBar(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiStatusBar(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiDummyRec(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);

    int ret = GuiDummyRec(arg0, arg1);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiGrid(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    double arg2;
    JS_ToFloat64(ctx, &arg2, argv[2]);
    int arg3;
    JS_ToInt32(ctx, &arg3, argv[3]);
    Vector2 * arg4 = (Vector2 *)JS_GetOpaque2(ctx, argv[4], js_Vector2_class_id);

    int ret = GuiGrid(arg0, arg1, arg2, arg3, arg4);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiListView(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "scrollIndex");
    int arg2_int;
    JS_ToInt32(ctx, &arg2_int, arg2_js);
    int * arg2 = &arg2_int;
                    JSValue arg3_js = JS_GetPropertyStr(ctx, argv[3], "active");
    int arg3_int;
    JS_ToInt32(ctx, &arg3_int, arg3_js);
    int * arg3 = &arg3_int;
                    
    int ret = GuiListView(arg0, arg1, arg2, arg3);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "scrollIndex", JS_NewInt32(ctx, arg2_int));
JS_SetPropertyStr(ctx, argv[3], "active", JS_NewInt32(ctx, arg3_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiMessageBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);
    const char * arg3 = (const char *)JS_ToCString(ctx, argv[3]);

    int ret = GuiMessageBox(arg0, arg1, arg2, arg3);

    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2);
    JS_FreeCString(ctx, arg3);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiTextInputBox(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    const char * arg2 = (const char *)JS_ToCString(ctx, argv[2]);
    const char * arg3 = (const char *)JS_ToCString(ctx, argv[3]);
    JSValue arg4_js = JS_GetPropertyStr(ctx, argv[4], "text");
    size_t arg4_len;
    const char * arg4_str = JS_ToCStringLen(ctx, &arg4_len, arg4_js);
    char * arg4 = malloc(arg4_len+1);
    memcpy((void *)arg4, arg4_str, arg4_len);
    arg4[arg4_len] = 0;
                    int arg5;
    JS_ToInt32(ctx, &arg5, argv[5]);
JSValue arg6_js = JS_GetPropertyStr(ctx, argv[6], "secretViewActive");
    int arg6_int;
    JS_ToInt32(ctx, &arg6_int, arg6_js);
    int * arg6 = &arg6_int;
                    
    int ret = GuiTextInputBox(arg0, arg1, arg2, arg3, arg4, arg5, arg6);

    JS_FreeCString(ctx, arg1);
    JS_FreeCString(ctx, arg2);
    JS_FreeCString(ctx, arg3);
    JS_FreeCString(ctx, arg4_str);
                JS_SetPropertyStr(ctx, argv[4], "text", JS_NewString(ctx, arg4));
                free(arg4);
JS_SetPropertyStr(ctx, argv[6], "secretViewActive", JS_NewInt32(ctx, arg6_int));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiColorPicker(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Color * arg2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);

    int ret = GuiColorPicker(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiColorPanel(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Color * arg2 = (Color *)JS_GetOpaque2(ctx, argv[2], js_Color_class_id);

    int ret = GuiColorPanel(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiColorBarAlpha(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "alpha");
    double arg2_double;
    JS_ToFloat64(ctx, &arg2_double, arg2_js);
    float  arg2_float = (float)arg2_double;
    float * arg2 = &arg2_float;
                    
    int ret = GuiColorBarAlpha(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "alpha", JS_NewFloat64(ctx, arg2_float));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiColorBarHue(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
JSValue arg2_js = JS_GetPropertyStr(ctx, argv[2], "value");
    double arg2_double;
    JS_ToFloat64(ctx, &arg2_double, arg2_js);
    float  arg2_float = (float)arg2_double;
    float * arg2 = &arg2_float;
                    
    int ret = GuiColorBarHue(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);
JS_SetPropertyStr(ctx, argv[2], "value", JS_NewFloat64(ctx, arg2_float));

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiColorPickerHSV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Vector3 * arg2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);

    int ret = GuiColorPickerHSV(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static JSValue js_GuiColorPanelHSV(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)
{
    Rectangle * argptr0 = (Rectangle *)JS_GetOpaque2(ctx, argv[0], js_Rectangle_class_id);
        if (argptr0 == NULL) return JS_EXCEPTION;
                    
        Rectangle arg0 = *argptr0;
    const char * arg1 = (const char *)JS_ToCString(ctx, argv[1]);
    Vector3 * arg2 = (Vector3 *)JS_GetOpaque2(ctx, argv[2], js_Vector3_class_id);

    int ret = GuiColorPanelHSV(arg0, arg1, arg2);

    JS_FreeCString(ctx, arg1);

    return JS_NewInt32(ctx, ret);
}

static const JSCFunctionListEntry js_raylib_funcs[] = {
    JS_CFUNC_DEF("InitWindow", 3, js_InitWindow ),
    JS_CFUNC_DEF("CloseWindow", 0, js_CloseWindow ),
    JS_CFUNC_DEF("WindowShouldClose", 0, js_WindowShouldClose ),
    JS_CFUNC_DEF("IsWindowReady", 0, js_IsWindowReady ),
    JS_CFUNC_DEF("IsWindowFullscreen", 0, js_IsWindowFullscreen ),
    JS_CFUNC_DEF("IsWindowHidden", 0, js_IsWindowHidden ),
    JS_CFUNC_DEF("IsWindowMinimized", 0, js_IsWindowMinimized ),
    JS_CFUNC_DEF("IsWindowMaximized", 0, js_IsWindowMaximized ),
    JS_CFUNC_DEF("IsWindowFocused", 0, js_IsWindowFocused ),
    JS_CFUNC_DEF("IsWindowResized", 0, js_IsWindowResized ),
    JS_CFUNC_DEF("IsWindowState", 1, js_IsWindowState ),
    JS_CFUNC_DEF("SetWindowState", 1, js_SetWindowState ),
    JS_CFUNC_DEF("ClearWindowState", 1, js_ClearWindowState ),
    JS_CFUNC_DEF("ToggleFullscreen", 0, js_ToggleFullscreen ),
    JS_CFUNC_DEF("ToggleBorderlessWindowed", 0, js_ToggleBorderlessWindowed ),
    JS_CFUNC_DEF("MaximizeWindow", 0, js_MaximizeWindow ),
    JS_CFUNC_DEF("MinimizeWindow", 0, js_MinimizeWindow ),
    JS_CFUNC_DEF("RestoreWindow", 0, js_RestoreWindow ),
    JS_CFUNC_DEF("SetWindowIcon", 1, js_SetWindowIcon ),
    JS_CFUNC_DEF("SetWindowTitle", 1, js_SetWindowTitle ),
    JS_CFUNC_DEF("SetWindowPosition", 2, js_SetWindowPosition ),
    JS_CFUNC_DEF("SetWindowMonitor", 1, js_SetWindowMonitor ),
    JS_CFUNC_DEF("SetWindowMinSize", 2, js_SetWindowMinSize ),
    JS_CFUNC_DEF("SetWindowMaxSize", 2, js_SetWindowMaxSize ),
    JS_CFUNC_DEF("SetWindowSize", 2, js_SetWindowSize ),
    JS_CFUNC_DEF("SetWindowOpacity", 1, js_SetWindowOpacity ),
    JS_CFUNC_DEF("SetWindowFocused", 0, js_SetWindowFocused ),
    JS_CFUNC_DEF("GetWindowHandle", 0, js_GetWindowHandle ),
    JS_CFUNC_DEF("GetScreenWidth", 0, js_GetScreenWidth ),
    JS_CFUNC_DEF("GetScreenHeight", 0, js_GetScreenHeight ),
    JS_CFUNC_DEF("GetRenderWidth", 0, js_GetRenderWidth ),
    JS_CFUNC_DEF("GetRenderHeight", 0, js_GetRenderHeight ),
    JS_CFUNC_DEF("GetMonitorCount", 0, js_GetMonitorCount ),
    JS_CFUNC_DEF("GetCurrentMonitor", 0, js_GetCurrentMonitor ),
    JS_CFUNC_DEF("GetMonitorPosition", 1, js_GetMonitorPosition ),
    JS_CFUNC_DEF("GetMonitorWidth", 1, js_GetMonitorWidth ),
    JS_CFUNC_DEF("GetMonitorHeight", 1, js_GetMonitorHeight ),
    JS_CFUNC_DEF("GetMonitorPhysicalWidth", 1, js_GetMonitorPhysicalWidth ),
    JS_CFUNC_DEF("GetMonitorPhysicalHeight", 1, js_GetMonitorPhysicalHeight ),
    JS_CFUNC_DEF("GetMonitorRefreshRate", 1, js_GetMonitorRefreshRate ),
    JS_CFUNC_DEF("GetWindowPosition", 0, js_GetWindowPosition ),
    JS_CFUNC_DEF("GetWindowScaleDPI", 0, js_GetWindowScaleDPI ),
    JS_CFUNC_DEF("GetMonitorName", 1, js_GetMonitorName ),
    JS_CFUNC_DEF("SetClipboardText", 1, js_SetClipboardText ),
    JS_CFUNC_DEF("GetClipboardText", 0, js_GetClipboardText ),
    JS_CFUNC_DEF("EnableEventWaiting", 0, js_EnableEventWaiting ),
    JS_CFUNC_DEF("DisableEventWaiting", 0, js_DisableEventWaiting ),
    JS_CFUNC_DEF("ShowCursor", 0, js_ShowCursor ),
    JS_CFUNC_DEF("HideCursor", 0, js_HideCursor ),
    JS_CFUNC_DEF("IsCursorHidden", 0, js_IsCursorHidden ),
    JS_CFUNC_DEF("EnableCursor", 0, js_EnableCursor ),
    JS_CFUNC_DEF("DisableCursor", 0, js_DisableCursor ),
    JS_CFUNC_DEF("IsCursorOnScreen", 0, js_IsCursorOnScreen ),
    JS_CFUNC_DEF("ClearBackground", 1, js_ClearBackground ),
    JS_CFUNC_DEF("BeginDrawing", 0, js_BeginDrawing ),
    JS_CFUNC_DEF("EndDrawing", 0, js_EndDrawing ),
    JS_CFUNC_DEF("BeginMode2D", 1, js_BeginMode2D ),
    JS_CFUNC_DEF("EndMode2D", 0, js_EndMode2D ),
    JS_CFUNC_DEF("BeginMode3D", 1, js_BeginMode3D ),
    JS_CFUNC_DEF("EndMode3D", 0, js_EndMode3D ),
    JS_CFUNC_DEF("BeginTextureMode", 1, js_BeginTextureMode ),
    JS_CFUNC_DEF("EndTextureMode", 0, js_EndTextureMode ),
    JS_CFUNC_DEF("BeginShaderMode", 1, js_BeginShaderMode ),
    JS_CFUNC_DEF("EndShaderMode", 0, js_EndShaderMode ),
    JS_CFUNC_DEF("BeginBlendMode", 1, js_BeginBlendMode ),
    JS_CFUNC_DEF("EndBlendMode", 0, js_EndBlendMode ),
    JS_CFUNC_DEF("BeginScissorMode", 4, js_BeginScissorMode ),
    JS_CFUNC_DEF("EndScissorMode", 0, js_EndScissorMode ),
    JS_CFUNC_DEF("BeginVrStereoMode", 1, js_BeginVrStereoMode ),
    JS_CFUNC_DEF("EndVrStereoMode", 0, js_EndVrStereoMode ),
    JS_CFUNC_DEF("LoadVrStereoConfig", 1, js_LoadVrStereoConfig ),
    JS_CFUNC_DEF("UnloadVrStereoConfig", 1, js_UnloadVrStereoConfig ),
    JS_CFUNC_DEF("LoadShader", 2, js_LoadShader ),
    JS_CFUNC_DEF("LoadShaderFromMemory", 2, js_LoadShaderFromMemory ),
    JS_CFUNC_DEF("IsShaderReady", 1, js_IsShaderReady ),
    JS_CFUNC_DEF("GetShaderLocation", 2, js_GetShaderLocation ),
    JS_CFUNC_DEF("GetShaderLocationAttrib", 2, js_GetShaderLocationAttrib ),
    JS_CFUNC_DEF("SetShaderValue", 4, js_SetShaderValue ),
    JS_CFUNC_DEF("SetShaderValueV", 5, js_SetShaderValueV ),
    JS_CFUNC_DEF("SetShaderValueMatrix", 3, js_SetShaderValueMatrix ),
    JS_CFUNC_DEF("SetShaderValueTexture", 3, js_SetShaderValueTexture ),
    JS_CFUNC_DEF("UnloadShader", 1, js_UnloadShader ),
    JS_CFUNC_DEF("GetMouseRay", 2, js_GetMouseRay ),
    JS_CFUNC_DEF("GetCameraMatrix", 1, js_GetCameraMatrix ),
    JS_CFUNC_DEF("GetCameraMatrix2D", 1, js_GetCameraMatrix2D ),
    JS_CFUNC_DEF("GetWorldToScreen", 2, js_GetWorldToScreen ),
    JS_CFUNC_DEF("GetScreenToWorld2D", 2, js_GetScreenToWorld2D ),
    JS_CFUNC_DEF("GetWorldToScreenEx", 4, js_GetWorldToScreenEx ),
    JS_CFUNC_DEF("GetWorldToScreen2D", 2, js_GetWorldToScreen2D ),
    JS_CFUNC_DEF("SetTargetFPS", 1, js_SetTargetFPS ),
    JS_CFUNC_DEF("GetFrameTime", 0, js_GetFrameTime ),
    JS_CFUNC_DEF("GetTime", 0, js_GetTime ),
    JS_CFUNC_DEF("GetFPS", 0, js_GetFPS ),
    JS_CFUNC_DEF("SwapScreenBuffer", 0, js_SwapScreenBuffer ),
    JS_CFUNC_DEF("PollInputEvents", 0, js_PollInputEvents ),
    JS_CFUNC_DEF("WaitTime", 1, js_WaitTime ),
    JS_CFUNC_DEF("SetRandomSeed", 1, js_SetRandomSeed ),
    JS_CFUNC_DEF("GetRandomValue", 2, js_GetRandomValue ),
    JS_CFUNC_DEF("LoadRandomSequence", 3, js_LoadRandomSequence ),
    JS_CFUNC_DEF("UnloadRandomSequence", 1, js_UnloadRandomSequence ),
    JS_CFUNC_DEF("TakeScreenshot", 1, js_TakeScreenshot ),
    JS_CFUNC_DEF("SetConfigFlags", 1, js_SetConfigFlags ),
    JS_CFUNC_DEF("OpenURL", 1, js_OpenURL ),
    JS_CFUNC_DEF("SetTraceLogLevel", 1, js_SetTraceLogLevel ),
    JS_CFUNC_DEF("MemAlloc", 1, js_MemAlloc ),
    JS_CFUNC_DEF("MemRealloc", 2, js_MemRealloc ),
    JS_CFUNC_DEF("MemFree", 1, js_MemFree ),
    JS_CFUNC_DEF("LoadFileData", 2, js_LoadFileData ),
    JS_CFUNC_DEF("SaveFileData", 3, js_SaveFileData ),
    JS_CFUNC_DEF("ExportDataAsCode", 3, js_ExportDataAsCode ),
    JS_CFUNC_DEF("LoadFileText", 1, js_LoadFileText ),
    JS_CFUNC_DEF("UnloadFileText", 0, js_UnloadFileText ),
    JS_CFUNC_DEF("SaveFileText", 2, js_SaveFileText ),
    JS_CFUNC_DEF("FileExists", 1, js_FileExists ),
    JS_CFUNC_DEF("DirectoryExists", 1, js_DirectoryExists ),
    JS_CFUNC_DEF("IsFileExtension", 2, js_IsFileExtension ),
    JS_CFUNC_DEF("GetFileLength", 1, js_GetFileLength ),
    JS_CFUNC_DEF("GetFileExtension", 1, js_GetFileExtension ),
    JS_CFUNC_DEF("GetFileName", 1, js_GetFileName ),
    JS_CFUNC_DEF("GetFileNameWithoutExt", 1, js_GetFileNameWithoutExt ),
    JS_CFUNC_DEF("GetDirectoryPath", 1, js_GetDirectoryPath ),
    JS_CFUNC_DEF("GetPrevDirectoryPath", 1, js_GetPrevDirectoryPath ),
    JS_CFUNC_DEF("GetWorkingDirectory", 0, js_GetWorkingDirectory ),
    JS_CFUNC_DEF("GetApplicationDirectory", 0, js_GetApplicationDirectory ),
    JS_CFUNC_DEF("ChangeDirectory", 1, js_ChangeDirectory ),
    JS_CFUNC_DEF("IsPathFile", 1, js_IsPathFile ),
    JS_CFUNC_DEF("LoadDirectoryFiles", 1, js_LoadDirectoryFiles ),
    JS_CFUNC_DEF("LoadDirectoryFilesEx", 3, js_LoadDirectoryFilesEx ),
    JS_CFUNC_DEF("UnloadDirectoryFiles", 1, js_UnloadDirectoryFiles ),
    JS_CFUNC_DEF("IsFileDropped", 0, js_IsFileDropped ),
    JS_CFUNC_DEF("LoadDroppedFiles", 0, js_LoadDroppedFiles ),
    JS_CFUNC_DEF("UnloadDroppedFiles", 1, js_UnloadDroppedFiles ),
    JS_CFUNC_DEF("GetFileModTime", 1, js_GetFileModTime ),
    JS_CFUNC_DEF("CompressData", 3, js_CompressData ),
    JS_CFUNC_DEF("DecompressData", 3, js_DecompressData ),
    JS_CFUNC_DEF("EncodeDataBase64", 3, js_EncodeDataBase64 ),
    JS_CFUNC_DEF("DecodeDataBase64", 2, js_DecodeDataBase64 ),
    JS_CFUNC_DEF("LoadAutomationEventList", 1, js_LoadAutomationEventList ),
    JS_CFUNC_DEF("UnloadAutomationEventList", 1, js_UnloadAutomationEventList ),
    JS_CFUNC_DEF("ExportAutomationEventList", 2, js_ExportAutomationEventList ),
    JS_CFUNC_DEF("SetAutomationEventList", 1, js_SetAutomationEventList ),
    JS_CFUNC_DEF("SetAutomationEventBaseFrame", 1, js_SetAutomationEventBaseFrame ),
    JS_CFUNC_DEF("StartAutomationEventRecording", 0, js_StartAutomationEventRecording ),
    JS_CFUNC_DEF("StopAutomationEventRecording", 0, js_StopAutomationEventRecording ),
    JS_CFUNC_DEF("PlayAutomationEvent", 1, js_PlayAutomationEvent ),
    JS_CFUNC_DEF("IsKeyPressed", 1, js_IsKeyPressed ),
    JS_CFUNC_DEF("IsKeyPressedRepeat", 1, js_IsKeyPressedRepeat ),
    JS_CFUNC_DEF("IsKeyDown", 1, js_IsKeyDown ),
    JS_CFUNC_DEF("IsKeyReleased", 1, js_IsKeyReleased ),
    JS_CFUNC_DEF("IsKeyUp", 1, js_IsKeyUp ),
    JS_CFUNC_DEF("GetKeyPressed", 0, js_GetKeyPressed ),
    JS_CFUNC_DEF("GetCharPressed", 0, js_GetCharPressed ),
    JS_CFUNC_DEF("SetExitKey", 1, js_SetExitKey ),
    JS_CFUNC_DEF("IsGamepadAvailable", 1, js_IsGamepadAvailable ),
    JS_CFUNC_DEF("GetGamepadName", 1, js_GetGamepadName ),
    JS_CFUNC_DEF("IsGamepadButtonPressed", 2, js_IsGamepadButtonPressed ),
    JS_CFUNC_DEF("IsGamepadButtonDown", 2, js_IsGamepadButtonDown ),
    JS_CFUNC_DEF("IsGamepadButtonReleased", 2, js_IsGamepadButtonReleased ),
    JS_CFUNC_DEF("IsGamepadButtonUp", 2, js_IsGamepadButtonUp ),
    JS_CFUNC_DEF("GetGamepadButtonPressed", 0, js_GetGamepadButtonPressed ),
    JS_CFUNC_DEF("GetGamepadAxisCount", 1, js_GetGamepadAxisCount ),
    JS_CFUNC_DEF("GetGamepadAxisMovement", 2, js_GetGamepadAxisMovement ),
    JS_CFUNC_DEF("SetGamepadMappings", 1, js_SetGamepadMappings ),
    JS_CFUNC_DEF("IsMouseButtonPressed", 1, js_IsMouseButtonPressed ),
    JS_CFUNC_DEF("IsMouseButtonDown", 1, js_IsMouseButtonDown ),
    JS_CFUNC_DEF("IsMouseButtonReleased", 1, js_IsMouseButtonReleased ),
    JS_CFUNC_DEF("IsMouseButtonUp", 1, js_IsMouseButtonUp ),
    JS_CFUNC_DEF("GetMouseX", 0, js_GetMouseX ),
    JS_CFUNC_DEF("GetMouseY", 0, js_GetMouseY ),
    JS_CFUNC_DEF("GetMousePosition", 0, js_GetMousePosition ),
    JS_CFUNC_DEF("GetMouseDelta", 0, js_GetMouseDelta ),
    JS_CFUNC_DEF("SetMousePosition", 2, js_SetMousePosition ),
    JS_CFUNC_DEF("SetMouseOffset", 2, js_SetMouseOffset ),
    JS_CFUNC_DEF("SetMouseScale", 2, js_SetMouseScale ),
    JS_CFUNC_DEF("GetMouseWheelMove", 0, js_GetMouseWheelMove ),
    JS_CFUNC_DEF("GetMouseWheelMoveV", 0, js_GetMouseWheelMoveV ),
    JS_CFUNC_DEF("SetMouseCursor", 1, js_SetMouseCursor ),
    JS_CFUNC_DEF("GetTouchX", 0, js_GetTouchX ),
    JS_CFUNC_DEF("GetTouchY", 0, js_GetTouchY ),
    JS_CFUNC_DEF("GetTouchPosition", 1, js_GetTouchPosition ),
    JS_CFUNC_DEF("GetTouchPointId", 1, js_GetTouchPointId ),
    JS_CFUNC_DEF("GetTouchPointCount", 0, js_GetTouchPointCount ),
    JS_CFUNC_DEF("SetGesturesEnabled", 1, js_SetGesturesEnabled ),
    JS_CFUNC_DEF("IsGestureDetected", 1, js_IsGestureDetected ),
    JS_CFUNC_DEF("GetGestureDetected", 0, js_GetGestureDetected ),
    JS_CFUNC_DEF("GetGestureHoldDuration", 0, js_GetGestureHoldDuration ),
    JS_CFUNC_DEF("GetGestureDragVector", 0, js_GetGestureDragVector ),
    JS_CFUNC_DEF("GetGestureDragAngle", 0, js_GetGestureDragAngle ),
    JS_CFUNC_DEF("GetGesturePinchVector", 0, js_GetGesturePinchVector ),
    JS_CFUNC_DEF("GetGesturePinchAngle", 0, js_GetGesturePinchAngle ),
    JS_CFUNC_DEF("UpdateCamera", 2, js_UpdateCamera ),
    JS_CFUNC_DEF("UpdateCameraPro", 4, js_UpdateCameraPro ),
    JS_CFUNC_DEF("SetShapesTexture", 2, js_SetShapesTexture ),
    JS_CFUNC_DEF("DrawPixel", 3, js_DrawPixel ),
    JS_CFUNC_DEF("DrawPixelV", 2, js_DrawPixelV ),
    JS_CFUNC_DEF("DrawLine", 5, js_DrawLine ),
    JS_CFUNC_DEF("DrawLineV", 3, js_DrawLineV ),
    JS_CFUNC_DEF("DrawLineEx", 4, js_DrawLineEx ),
    JS_CFUNC_DEF("DrawLineBezier", 4, js_DrawLineBezier ),
    JS_CFUNC_DEF("DrawCircle", 4, js_DrawCircle ),
    JS_CFUNC_DEF("DrawCircleSector", 6, js_DrawCircleSector ),
    JS_CFUNC_DEF("DrawCircleSectorLines", 6, js_DrawCircleSectorLines ),
    JS_CFUNC_DEF("DrawCircleGradient", 5, js_DrawCircleGradient ),
    JS_CFUNC_DEF("DrawCircleV", 3, js_DrawCircleV ),
    JS_CFUNC_DEF("DrawCircleLines", 4, js_DrawCircleLines ),
    JS_CFUNC_DEF("DrawCircleLinesV", 3, js_DrawCircleLinesV ),
    JS_CFUNC_DEF("DrawEllipse", 5, js_DrawEllipse ),
    JS_CFUNC_DEF("DrawEllipseLines", 5, js_DrawEllipseLines ),
    JS_CFUNC_DEF("DrawRing", 7, js_DrawRing ),
    JS_CFUNC_DEF("DrawRingLines", 7, js_DrawRingLines ),
    JS_CFUNC_DEF("DrawRectangle", 5, js_DrawRectangle ),
    JS_CFUNC_DEF("DrawRectangleV", 3, js_DrawRectangleV ),
    JS_CFUNC_DEF("DrawRectangleRec", 2, js_DrawRectangleRec ),
    JS_CFUNC_DEF("DrawRectanglePro", 4, js_DrawRectanglePro ),
    JS_CFUNC_DEF("DrawRectangleGradientV", 6, js_DrawRectangleGradientV ),
    JS_CFUNC_DEF("DrawRectangleGradientH", 6, js_DrawRectangleGradientH ),
    JS_CFUNC_DEF("DrawRectangleGradientEx", 5, js_DrawRectangleGradientEx ),
    JS_CFUNC_DEF("DrawRectangleLines", 5, js_DrawRectangleLines ),
    JS_CFUNC_DEF("DrawRectangleLinesEx", 3, js_DrawRectangleLinesEx ),
    JS_CFUNC_DEF("DrawRectangleRounded", 4, js_DrawRectangleRounded ),
    JS_CFUNC_DEF("DrawRectangleRoundedLines", 5, js_DrawRectangleRoundedLines ),
    JS_CFUNC_DEF("DrawTriangle", 4, js_DrawTriangle ),
    JS_CFUNC_DEF("DrawTriangleLines", 4, js_DrawTriangleLines ),
    JS_CFUNC_DEF("DrawPoly", 5, js_DrawPoly ),
    JS_CFUNC_DEF("DrawPolyLines", 5, js_DrawPolyLines ),
    JS_CFUNC_DEF("DrawPolyLinesEx", 6, js_DrawPolyLinesEx ),
    JS_CFUNC_DEF("DrawSplineSegmentLinear", 4, js_DrawSplineSegmentLinear ),
    JS_CFUNC_DEF("DrawSplineSegmentBasis", 6, js_DrawSplineSegmentBasis ),
    JS_CFUNC_DEF("DrawSplineSegmentCatmullRom", 6, js_DrawSplineSegmentCatmullRom ),
    JS_CFUNC_DEF("DrawSplineSegmentBezierQuadratic", 5, js_DrawSplineSegmentBezierQuadratic ),
    JS_CFUNC_DEF("DrawSplineSegmentBezierCubic", 6, js_DrawSplineSegmentBezierCubic ),
    JS_CFUNC_DEF("GetSplinePointLinear", 3, js_GetSplinePointLinear ),
    JS_CFUNC_DEF("GetSplinePointBasis", 5, js_GetSplinePointBasis ),
    JS_CFUNC_DEF("GetSplinePointCatmullRom", 5, js_GetSplinePointCatmullRom ),
    JS_CFUNC_DEF("GetSplinePointBezierQuad", 4, js_GetSplinePointBezierQuad ),
    JS_CFUNC_DEF("GetSplinePointBezierCubic", 5, js_GetSplinePointBezierCubic ),
    JS_CFUNC_DEF("CheckCollisionRecs", 2, js_CheckCollisionRecs ),
    JS_CFUNC_DEF("CheckCollisionCircles", 4, js_CheckCollisionCircles ),
    JS_CFUNC_DEF("CheckCollisionCircleRec", 3, js_CheckCollisionCircleRec ),
    JS_CFUNC_DEF("CheckCollisionPointRec", 2, js_CheckCollisionPointRec ),
    JS_CFUNC_DEF("CheckCollisionPointCircle", 3, js_CheckCollisionPointCircle ),
    JS_CFUNC_DEF("CheckCollisionPointTriangle", 4, js_CheckCollisionPointTriangle ),
    JS_CFUNC_DEF("CheckCollisionPointLine", 4, js_CheckCollisionPointLine ),
    JS_CFUNC_DEF("GetCollisionRec", 2, js_GetCollisionRec ),
    JS_CFUNC_DEF("LoadImage", 1, js_LoadImage ),
    JS_CFUNC_DEF("LoadImageRaw", 5, js_LoadImageRaw ),
    JS_CFUNC_DEF("LoadImageSvg", 3, js_LoadImageSvg ),
    JS_CFUNC_DEF("LoadImageAnim", 2, js_LoadImageAnim ),
    JS_CFUNC_DEF("LoadImageFromMemory", 3, js_LoadImageFromMemory ),
    JS_CFUNC_DEF("LoadImageFromTexture", 1, js_LoadImageFromTexture ),
    JS_CFUNC_DEF("LoadImageFromScreen", 0, js_LoadImageFromScreen ),
    JS_CFUNC_DEF("IsImageReady", 1, js_IsImageReady ),
    JS_CFUNC_DEF("UnloadImage", 1, js_UnloadImage ),
    JS_CFUNC_DEF("ExportImage", 2, js_ExportImage ),
    JS_CFUNC_DEF("ExportImageToMemory", 3, js_ExportImageToMemory ),
    JS_CFUNC_DEF("ExportImageAsCode", 2, js_ExportImageAsCode ),
    JS_CFUNC_DEF("GenImageColor", 3, js_GenImageColor ),
    JS_CFUNC_DEF("GenImageGradientLinear", 5, js_GenImageGradientLinear ),
    JS_CFUNC_DEF("GenImageGradientRadial", 5, js_GenImageGradientRadial ),
    JS_CFUNC_DEF("GenImageGradientSquare", 5, js_GenImageGradientSquare ),
    JS_CFUNC_DEF("GenImageChecked", 6, js_GenImageChecked ),
    JS_CFUNC_DEF("GenImageWhiteNoise", 3, js_GenImageWhiteNoise ),
    JS_CFUNC_DEF("GenImagePerlinNoise", 5, js_GenImagePerlinNoise ),
    JS_CFUNC_DEF("GenImageCellular", 3, js_GenImageCellular ),
    JS_CFUNC_DEF("GenImageText", 3, js_GenImageText ),
    JS_CFUNC_DEF("GetImageAlphaBorder", 2, js_GetImageAlphaBorder ),
    JS_CFUNC_DEF("GetImageColor", 3, js_GetImageColor ),
    JS_CFUNC_DEF("LoadTexture", 1, js_LoadTexture ),
    JS_CFUNC_DEF("LoadTextureFromImage", 1, js_LoadTextureFromImage ),
    JS_CFUNC_DEF("LoadTextureCubemap", 2, js_LoadTextureCubemap ),
    JS_CFUNC_DEF("LoadRenderTexture", 2, js_LoadRenderTexture ),
    JS_CFUNC_DEF("IsTextureReady", 1, js_IsTextureReady ),
    JS_CFUNC_DEF("UnloadTexture", 1, js_UnloadTexture ),
    JS_CFUNC_DEF("IsRenderTextureReady", 1, js_IsRenderTextureReady ),
    JS_CFUNC_DEF("UnloadRenderTexture", 1, js_UnloadRenderTexture ),
    JS_CFUNC_DEF("UpdateTexture", 2, js_UpdateTexture ),
    JS_CFUNC_DEF("UpdateTextureRec", 3, js_UpdateTextureRec ),
    JS_CFUNC_DEF("SetTextureFilter", 2, js_SetTextureFilter ),
    JS_CFUNC_DEF("SetTextureWrap", 2, js_SetTextureWrap ),
    JS_CFUNC_DEF("DrawTexture", 4, js_DrawTexture ),
    JS_CFUNC_DEF("DrawTextureV", 3, js_DrawTextureV ),
    JS_CFUNC_DEF("DrawTextureEx", 5, js_DrawTextureEx ),
    JS_CFUNC_DEF("DrawTextureRec", 4, js_DrawTextureRec ),
    JS_CFUNC_DEF("DrawTexturePro", 6, js_DrawTexturePro ),
    JS_CFUNC_DEF("DrawTextureNPatch", 6, js_DrawTextureNPatch ),
    JS_CFUNC_DEF("Fade", 2, js_Fade ),
    JS_CFUNC_DEF("ColorToInt", 1, js_ColorToInt ),
    JS_CFUNC_DEF("ColorNormalize", 1, js_ColorNormalize ),
    JS_CFUNC_DEF("ColorFromNormalized", 1, js_ColorFromNormalized ),
    JS_CFUNC_DEF("ColorToHSV", 1, js_ColorToHSV ),
    JS_CFUNC_DEF("ColorFromHSV", 3, js_ColorFromHSV ),
    JS_CFUNC_DEF("ColorTint", 2, js_ColorTint ),
    JS_CFUNC_DEF("ColorBrightness", 2, js_ColorBrightness ),
    JS_CFUNC_DEF("ColorContrast", 2, js_ColorContrast ),
    JS_CFUNC_DEF("ColorAlpha", 2, js_ColorAlpha ),
    JS_CFUNC_DEF("ColorAlphaBlend", 3, js_ColorAlphaBlend ),
    JS_CFUNC_DEF("GetColor", 1, js_GetColor ),
    JS_CFUNC_DEF("GetPixelColor", 2, js_GetPixelColor ),
    JS_CFUNC_DEF("SetPixelColor", 3, js_SetPixelColor ),
    JS_CFUNC_DEF("GetPixelDataSize", 3, js_GetPixelDataSize ),
    JS_CFUNC_DEF("GetFontDefault", 0, js_GetFontDefault ),
    JS_CFUNC_DEF("LoadFont", 1, js_LoadFont ),
    JS_CFUNC_DEF("LoadFontEx", 4, js_LoadFontEx ),
    JS_CFUNC_DEF("LoadFontFromImage", 3, js_LoadFontFromImage ),
    JS_CFUNC_DEF("LoadFontFromMemory", 6, js_LoadFontFromMemory ),
    JS_CFUNC_DEF("IsFontReady", 1, js_IsFontReady ),
    JS_CFUNC_DEF("UnloadFont", 1, js_UnloadFont ),
    JS_CFUNC_DEF("ExportFontAsCode", 2, js_ExportFontAsCode ),
    JS_CFUNC_DEF("DrawFPS", 2, js_DrawFPS ),
    JS_CFUNC_DEF("DrawText", 5, js_DrawText ),
    JS_CFUNC_DEF("DrawTextEx", 6, js_DrawTextEx ),
    JS_CFUNC_DEF("DrawTextPro", 8, js_DrawTextPro ),
    JS_CFUNC_DEF("DrawTextCodepoint", 5, js_DrawTextCodepoint ),
    JS_CFUNC_DEF("DrawTextCodepoints", 7, js_DrawTextCodepoints ),
    JS_CFUNC_DEF("SetTextLineSpacing", 1, js_SetTextLineSpacing ),
    JS_CFUNC_DEF("MeasureText", 2, js_MeasureText ),
    JS_CFUNC_DEF("MeasureTextEx", 4, js_MeasureTextEx ),
    JS_CFUNC_DEF("GetGlyphIndex", 2, js_GetGlyphIndex ),
    JS_CFUNC_DEF("GetGlyphInfo", 2, js_GetGlyphInfo ),
    JS_CFUNC_DEF("GetGlyphAtlasRec", 2, js_GetGlyphAtlasRec ),
    JS_CFUNC_DEF("LoadUTF8", 2, js_LoadUTF8 ),
    JS_CFUNC_DEF("UnloadUTF8", 1, js_UnloadUTF8 ),
    JS_CFUNC_DEF("LoadCodepoints", 2, js_LoadCodepoints ),
    JS_CFUNC_DEF("UnloadCodepoints", 1, js_UnloadCodepoints ),
    JS_CFUNC_DEF("GetCodepointCount", 1, js_GetCodepointCount ),
    JS_CFUNC_DEF("GetCodepoint", 2, js_GetCodepoint ),
    JS_CFUNC_DEF("GetCodepointNext", 2, js_GetCodepointNext ),
    JS_CFUNC_DEF("GetCodepointPrevious", 2, js_GetCodepointPrevious ),
    JS_CFUNC_DEF("CodepointToUTF8", 2, js_CodepointToUTF8 ),
    JS_CFUNC_DEF("TextCopy", 2, js_TextCopy ),
    JS_CFUNC_DEF("TextIsEqual", 2, js_TextIsEqual ),
    JS_CFUNC_DEF("TextLength", 1, js_TextLength ),
    JS_CFUNC_DEF("TextSubtext", 3, js_TextSubtext ),
    JS_CFUNC_DEF("TextReplace", 3, js_TextReplace ),
    JS_CFUNC_DEF("TextInsert", 3, js_TextInsert ),
    JS_CFUNC_DEF("TextAppend", 3, js_TextAppend ),
    JS_CFUNC_DEF("TextFindIndex", 2, js_TextFindIndex ),
    JS_CFUNC_DEF("TextToUpper", 1, js_TextToUpper ),
    JS_CFUNC_DEF("TextToLower", 1, js_TextToLower ),
    JS_CFUNC_DEF("TextToPascal", 1, js_TextToPascal ),
    JS_CFUNC_DEF("TextToInteger", 1, js_TextToInteger ),
    JS_CFUNC_DEF("DrawLine3D", 3, js_DrawLine3D ),
    JS_CFUNC_DEF("DrawPoint3D", 2, js_DrawPoint3D ),
    JS_CFUNC_DEF("DrawCircle3D", 5, js_DrawCircle3D ),
    JS_CFUNC_DEF("DrawTriangle3D", 4, js_DrawTriangle3D ),
    JS_CFUNC_DEF("DrawCube", 5, js_DrawCube ),
    JS_CFUNC_DEF("DrawCubeV", 3, js_DrawCubeV ),
    JS_CFUNC_DEF("DrawCubeWires", 5, js_DrawCubeWires ),
    JS_CFUNC_DEF("DrawCubeWiresV", 3, js_DrawCubeWiresV ),
    JS_CFUNC_DEF("DrawSphere", 3, js_DrawSphere ),
    JS_CFUNC_DEF("DrawSphereEx", 5, js_DrawSphereEx ),
    JS_CFUNC_DEF("DrawSphereWires", 5, js_DrawSphereWires ),
    JS_CFUNC_DEF("DrawCylinder", 6, js_DrawCylinder ),
    JS_CFUNC_DEF("DrawCylinderEx", 6, js_DrawCylinderEx ),
    JS_CFUNC_DEF("DrawCylinderWires", 6, js_DrawCylinderWires ),
    JS_CFUNC_DEF("DrawCylinderWiresEx", 6, js_DrawCylinderWiresEx ),
    JS_CFUNC_DEF("DrawCapsule", 6, js_DrawCapsule ),
    JS_CFUNC_DEF("DrawCapsuleWires", 6, js_DrawCapsuleWires ),
    JS_CFUNC_DEF("DrawPlane", 3, js_DrawPlane ),
    JS_CFUNC_DEF("DrawRay", 2, js_DrawRay ),
    JS_CFUNC_DEF("DrawGrid", 2, js_DrawGrid ),
    JS_CFUNC_DEF("LoadModel", 1, js_LoadModel ),
    JS_CFUNC_DEF("LoadModelFromMesh", 1, js_LoadModelFromMesh ),
    JS_CFUNC_DEF("IsModelReady", 1, js_IsModelReady ),
    JS_CFUNC_DEF("UnloadModel", 1, js_UnloadModel ),
    JS_CFUNC_DEF("GetModelBoundingBox", 1, js_GetModelBoundingBox ),
    JS_CFUNC_DEF("DrawModel", 4, js_DrawModel ),
    JS_CFUNC_DEF("DrawModelEx", 6, js_DrawModelEx ),
    JS_CFUNC_DEF("DrawModelWires", 4, js_DrawModelWires ),
    JS_CFUNC_DEF("DrawModelWiresEx", 6, js_DrawModelWiresEx ),
    JS_CFUNC_DEF("DrawBoundingBox", 2, js_DrawBoundingBox ),
    JS_CFUNC_DEF("DrawBillboard", 5, js_DrawBillboard ),
    JS_CFUNC_DEF("DrawBillboardRec", 6, js_DrawBillboardRec ),
    JS_CFUNC_DEF("DrawBillboardPro", 9, js_DrawBillboardPro ),
    JS_CFUNC_DEF("UpdateMeshBuffer", 5, js_UpdateMeshBuffer ),
    JS_CFUNC_DEF("UnloadMesh", 1, js_UnloadMesh ),
    JS_CFUNC_DEF("DrawMesh", 3, js_DrawMesh ),
    JS_CFUNC_DEF("ExportMesh", 2, js_ExportMesh ),
    JS_CFUNC_DEF("GetMeshBoundingBox", 1, js_GetMeshBoundingBox ),
    JS_CFUNC_DEF("GenMeshPoly", 2, js_GenMeshPoly ),
    JS_CFUNC_DEF("GenMeshPlane", 4, js_GenMeshPlane ),
    JS_CFUNC_DEF("GenMeshCube", 3, js_GenMeshCube ),
    JS_CFUNC_DEF("GenMeshSphere", 3, js_GenMeshSphere ),
    JS_CFUNC_DEF("GenMeshHemiSphere", 3, js_GenMeshHemiSphere ),
    JS_CFUNC_DEF("GenMeshCylinder", 3, js_GenMeshCylinder ),
    JS_CFUNC_DEF("GenMeshCone", 3, js_GenMeshCone ),
    JS_CFUNC_DEF("GenMeshTorus", 4, js_GenMeshTorus ),
    JS_CFUNC_DEF("GenMeshKnot", 4, js_GenMeshKnot ),
    JS_CFUNC_DEF("GenMeshHeightmap", 2, js_GenMeshHeightmap ),
    JS_CFUNC_DEF("GenMeshCubicmap", 2, js_GenMeshCubicmap ),
    JS_CFUNC_DEF("LoadMaterialDefault", 0, js_LoadMaterialDefault ),
    JS_CFUNC_DEF("IsMaterialReady", 1, js_IsMaterialReady ),
    JS_CFUNC_DEF("UnloadMaterial", 1, js_UnloadMaterial ),
    JS_CFUNC_DEF("UpdateModelAnimation", 3, js_UpdateModelAnimation ),
    JS_CFUNC_DEF("UnloadModelAnimation", 1, js_UnloadModelAnimation ),
    JS_CFUNC_DEF("IsModelAnimationValid", 2, js_IsModelAnimationValid ),
    JS_CFUNC_DEF("CheckCollisionSpheres", 4, js_CheckCollisionSpheres ),
    JS_CFUNC_DEF("CheckCollisionBoxes", 2, js_CheckCollisionBoxes ),
    JS_CFUNC_DEF("CheckCollisionBoxSphere", 3, js_CheckCollisionBoxSphere ),
    JS_CFUNC_DEF("GetRayCollisionSphere", 3, js_GetRayCollisionSphere ),
    JS_CFUNC_DEF("GetRayCollisionBox", 2, js_GetRayCollisionBox ),
    JS_CFUNC_DEF("GetRayCollisionMesh", 3, js_GetRayCollisionMesh ),
    JS_CFUNC_DEF("GetRayCollisionTriangle", 4, js_GetRayCollisionTriangle ),
    JS_CFUNC_DEF("GetRayCollisionQuad", 5, js_GetRayCollisionQuad ),
    JS_CFUNC_DEF("InitAudioDevice", 0, js_InitAudioDevice ),
    JS_CFUNC_DEF("CloseAudioDevice", 0, js_CloseAudioDevice ),
    JS_CFUNC_DEF("IsAudioDeviceReady", 0, js_IsAudioDeviceReady ),
    JS_CFUNC_DEF("SetMasterVolume", 1, js_SetMasterVolume ),
    JS_CFUNC_DEF("GetMasterVolume", 0, js_GetMasterVolume ),
    JS_CFUNC_DEF("LoadWave", 1, js_LoadWave ),
    JS_CFUNC_DEF("LoadWaveFromMemory", 3, js_LoadWaveFromMemory ),
    JS_CFUNC_DEF("IsWaveReady", 1, js_IsWaveReady ),
    JS_CFUNC_DEF("LoadSound", 1, js_LoadSound ),
    JS_CFUNC_DEF("LoadSoundFromWave", 1, js_LoadSoundFromWave ),
    JS_CFUNC_DEF("LoadSoundAlias", 1, js_LoadSoundAlias ),
    JS_CFUNC_DEF("IsSoundReady", 1, js_IsSoundReady ),
    JS_CFUNC_DEF("UpdateSound", 3, js_UpdateSound ),
    JS_CFUNC_DEF("UnloadWave", 1, js_UnloadWave ),
    JS_CFUNC_DEF("UnloadSound", 1, js_UnloadSound ),
    JS_CFUNC_DEF("UnloadSoundAlias", 1, js_UnloadSoundAlias ),
    JS_CFUNC_DEF("ExportWave", 2, js_ExportWave ),
    JS_CFUNC_DEF("ExportWaveAsCode", 2, js_ExportWaveAsCode ),
    JS_CFUNC_DEF("PlaySound", 1, js_PlaySound ),
    JS_CFUNC_DEF("StopSound", 1, js_StopSound ),
    JS_CFUNC_DEF("PauseSound", 1, js_PauseSound ),
    JS_CFUNC_DEF("ResumeSound", 1, js_ResumeSound ),
    JS_CFUNC_DEF("IsSoundPlaying", 1, js_IsSoundPlaying ),
    JS_CFUNC_DEF("SetSoundVolume", 2, js_SetSoundVolume ),
    JS_CFUNC_DEF("SetSoundPitch", 2, js_SetSoundPitch ),
    JS_CFUNC_DEF("SetSoundPan", 2, js_SetSoundPan ),
    JS_CFUNC_DEF("WaveCopy", 1, js_WaveCopy ),
    JS_CFUNC_DEF("LoadWaveSamples", 1, js_LoadWaveSamples ),
    JS_CFUNC_DEF("LoadMusicStream", 1, js_LoadMusicStream ),
    JS_CFUNC_DEF("LoadMusicStreamFromMemory", 3, js_LoadMusicStreamFromMemory ),
    JS_CFUNC_DEF("IsMusicReady", 1, js_IsMusicReady ),
    JS_CFUNC_DEF("UnloadMusicStream", 1, js_UnloadMusicStream ),
    JS_CFUNC_DEF("PlayMusicStream", 1, js_PlayMusicStream ),
    JS_CFUNC_DEF("IsMusicStreamPlaying", 1, js_IsMusicStreamPlaying ),
    JS_CFUNC_DEF("UpdateMusicStream", 1, js_UpdateMusicStream ),
    JS_CFUNC_DEF("StopMusicStream", 1, js_StopMusicStream ),
    JS_CFUNC_DEF("PauseMusicStream", 1, js_PauseMusicStream ),
    JS_CFUNC_DEF("ResumeMusicStream", 1, js_ResumeMusicStream ),
    JS_CFUNC_DEF("SeekMusicStream", 2, js_SeekMusicStream ),
    JS_CFUNC_DEF("SetMusicVolume", 2, js_SetMusicVolume ),
    JS_CFUNC_DEF("SetMusicPitch", 2, js_SetMusicPitch ),
    JS_CFUNC_DEF("SetMusicPan", 2, js_SetMusicPan ),
    JS_CFUNC_DEF("GetMusicTimeLength", 1, js_GetMusicTimeLength ),
    JS_CFUNC_DEF("GetMusicTimePlayed", 1, js_GetMusicTimePlayed ),
    JS_CFUNC_DEF("LoadAudioStream", 3, js_LoadAudioStream ),
    JS_CFUNC_DEF("IsAudioStreamReady", 1, js_IsAudioStreamReady ),
    JS_CFUNC_DEF("UnloadAudioStream", 1, js_UnloadAudioStream ),
    JS_CFUNC_DEF("UpdateAudioStream", 3, js_UpdateAudioStream ),
    JS_CFUNC_DEF("IsAudioStreamProcessed", 1, js_IsAudioStreamProcessed ),
    JS_CFUNC_DEF("PlayAudioStream", 1, js_PlayAudioStream ),
    JS_CFUNC_DEF("PauseAudioStream", 1, js_PauseAudioStream ),
    JS_CFUNC_DEF("ResumeAudioStream", 1, js_ResumeAudioStream ),
    JS_CFUNC_DEF("IsAudioStreamPlaying", 1, js_IsAudioStreamPlaying ),
    JS_CFUNC_DEF("StopAudioStream", 1, js_StopAudioStream ),
    JS_CFUNC_DEF("SetAudioStreamVolume", 2, js_SetAudioStreamVolume ),
    JS_CFUNC_DEF("SetAudioStreamPitch", 2, js_SetAudioStreamPitch ),
    JS_CFUNC_DEF("SetAudioStreamPan", 2, js_SetAudioStreamPan ),
    JS_CFUNC_DEF("SetAudioStreamBufferSizeDefault", 1, js_SetAudioStreamBufferSizeDefault ),
    JS_CFUNC_DEF("GetCameraForward", 1, js_GetCameraForward ),
    JS_CFUNC_DEF("GetCameraUp", 1, js_GetCameraUp ),
    JS_CFUNC_DEF("GetCameraRight", 1, js_GetCameraRight ),
    JS_CFUNC_DEF("CameraMoveForward", 3, js_CameraMoveForward ),
    JS_CFUNC_DEF("CameraMoveUp", 2, js_CameraMoveUp ),
    JS_CFUNC_DEF("CameraMoveRight", 3, js_CameraMoveRight ),
    JS_CFUNC_DEF("CameraMoveToTarget", 2, js_CameraMoveToTarget ),
    JS_CFUNC_DEF("CameraYaw", 3, js_CameraYaw ),
    JS_CFUNC_DEF("CameraPitch", 5, js_CameraPitch ),
    JS_CFUNC_DEF("CameraRoll", 2, js_CameraRoll ),
    JS_CFUNC_DEF("GetCameraViewMatrix", 1, js_GetCameraViewMatrix ),
    JS_CFUNC_DEF("GetCameraProjectionMatrix", 2, js_GetCameraProjectionMatrix ),
    JS_CFUNC_DEF("GuiEnable", 0, js_GuiEnable ),
    JS_CFUNC_DEF("GuiDisable", 0, js_GuiDisable ),
    JS_CFUNC_DEF("GuiLock", 0, js_GuiLock ),
    JS_CFUNC_DEF("GuiUnlock", 0, js_GuiUnlock ),
    JS_CFUNC_DEF("GuiIsLocked", 0, js_GuiIsLocked ),
    JS_CFUNC_DEF("GuiSetAlpha", 1, js_GuiSetAlpha ),
    JS_CFUNC_DEF("GuiSetState", 1, js_GuiSetState ),
    JS_CFUNC_DEF("GuiGetState", 0, js_GuiGetState ),
    JS_CFUNC_DEF("GuiSetFont", 1, js_GuiSetFont ),
    JS_CFUNC_DEF("GuiGetFont", 0, js_GuiGetFont ),
    JS_CFUNC_DEF("GuiSetStyle", 3, js_GuiSetStyle ),
    JS_CFUNC_DEF("GuiGetStyle", 2, js_GuiGetStyle ),
    JS_CFUNC_DEF("GuiLoadStyle", 1, js_GuiLoadStyle ),
    JS_CFUNC_DEF("GuiLoadStyleDefault", 0, js_GuiLoadStyleDefault ),
    JS_CFUNC_DEF("GuiEnableTooltip", 0, js_GuiEnableTooltip ),
    JS_CFUNC_DEF("GuiDisableTooltip", 0, js_GuiDisableTooltip ),
    JS_CFUNC_DEF("GuiSetTooltip", 1, js_GuiSetTooltip ),
    JS_CFUNC_DEF("GuiIconText", 2, js_GuiIconText ),
    JS_CFUNC_DEF("GuiSetIconScale", 1, js_GuiSetIconScale ),
    JS_CFUNC_DEF("GuiLoadIcons", 2, js_GuiLoadIcons ),
    JS_CFUNC_DEF("GuiDrawIcon", 5, js_GuiDrawIcon ),
    JS_CFUNC_DEF("GuiWindowBox", 2, js_GuiWindowBox ),
    JS_CFUNC_DEF("GuiGroupBox", 2, js_GuiGroupBox ),
    JS_CFUNC_DEF("GuiLine", 2, js_GuiLine ),
    JS_CFUNC_DEF("GuiPanel", 2, js_GuiPanel ),
    JS_CFUNC_DEF("GuiTabBar", 4, js_GuiTabBar ),
    JS_CFUNC_DEF("GuiScrollPanel", 5, js_GuiScrollPanel ),
    JS_CFUNC_DEF("GuiLabel", 2, js_GuiLabel ),
    JS_CFUNC_DEF("GuiButton", 2, js_GuiButton ),
    JS_CFUNC_DEF("GuiLabelButton", 2, js_GuiLabelButton ),
    JS_CFUNC_DEF("GuiToggle", 3, js_GuiToggle ),
    JS_CFUNC_DEF("GuiToggleGroup", 3, js_GuiToggleGroup ),
    JS_CFUNC_DEF("GuiToggleSlider", 3, js_GuiToggleSlider ),
    JS_CFUNC_DEF("GuiCheckBox", 3, js_GuiCheckBox ),
    JS_CFUNC_DEF("GuiComboBox", 3, js_GuiComboBox ),
    JS_CFUNC_DEF("GuiDropdownBox", 4, js_GuiDropdownBox ),
    JS_CFUNC_DEF("GuiSpinner", 6, js_GuiSpinner ),
    JS_CFUNC_DEF("GuiValueBox", 6, js_GuiValueBox ),
    JS_CFUNC_DEF("GuiValueBoxFloat", 5, js_GuiValueBoxFloat ),
    JS_CFUNC_DEF("GuiTextBox", 4, js_GuiTextBox ),
    JS_CFUNC_DEF("GuiSlider", 6, js_GuiSlider ),
    JS_CFUNC_DEF("GuiSliderBar", 6, js_GuiSliderBar ),
    JS_CFUNC_DEF("GuiProgressBar", 6, js_GuiProgressBar ),
    JS_CFUNC_DEF("GuiStatusBar", 2, js_GuiStatusBar ),
    JS_CFUNC_DEF("GuiDummyRec", 2, js_GuiDummyRec ),
    JS_CFUNC_DEF("GuiGrid", 5, js_GuiGrid ),
    JS_CFUNC_DEF("GuiListView", 4, js_GuiListView ),
    JS_CFUNC_DEF("GuiMessageBox", 4, js_GuiMessageBox ),
    JS_CFUNC_DEF("GuiTextInputBox", 7, js_GuiTextInputBox ),
    JS_CFUNC_DEF("GuiColorPicker", 3, js_GuiColorPicker ),
    JS_CFUNC_DEF("GuiColorPanel", 3, js_GuiColorPanel ),
    JS_CFUNC_DEF("GuiColorBarAlpha", 3, js_GuiColorBarAlpha ),
    JS_CFUNC_DEF("GuiColorBarHue", 3, js_GuiColorBarHue ),
    JS_CFUNC_DEF("GuiColorPickerHSV", 3, js_GuiColorPickerHSV ),
    JS_CFUNC_DEF("GuiColorPanelHSV", 3, js_GuiColorPanelHSV ),
};
static int js_raylib_init(JSContext *ctx, JSModuleDef *m)
{
    JS_SetModuleExportList(ctx, m, js_raylib_funcs, countof(js_raylib_funcs));

    js_declare_Vector2(ctx, m);
    js_declare_Vector3(ctx, m);
    js_declare_Vector4(ctx, m);
    js_declare_Quaternion(ctx, m);
    js_declare_Matrix(ctx, m);
    js_declare_Color(ctx, m);
    js_declare_Rectangle(ctx, m);
    js_declare_Image(ctx, m);
    js_declare_Texture(ctx, m);
    js_declare_Texture2D(ctx, m);
    js_declare_TextureCubemap(ctx, m);
    js_declare_RenderTexture(ctx, m);
    js_declare_RenderTexture2D(ctx, m);
    js_declare_NPatchInfo(ctx, m);
    js_declare_GlyphInfo(ctx, m);
    js_declare_Font(ctx, m);
    js_declare_Camera3D(ctx, m);
    js_declare_Camera(ctx, m);
    js_declare_Camera2D(ctx, m);
    js_declare_Mesh(ctx, m);
    js_declare_Shader(ctx, m);
    js_declare_MaterialMap(ctx, m);
    js_declare_Material(ctx, m);
    js_declare_Transform(ctx, m);
    js_declare_BoneInfo(ctx, m);
    js_declare_Model(ctx, m);
    js_declare_ModelAnimation(ctx, m);
    js_declare_Ray(ctx, m);
    js_declare_RayCollision(ctx, m);
    js_declare_BoundingBox(ctx, m);
    js_declare_Wave(ctx, m);
    js_declare_AudioStream(ctx, m);
    js_declare_Sound(ctx, m);
    js_declare_Music(ctx, m);
    js_declare_VrDeviceInfo(ctx, m);
    js_declare_VrStereoConfig(ctx, m);
    js_declare_FilePathList(ctx, m);
    js_declare_AutomationEvent(ctx, m);
    js_declare_AutomationEventList(ctx, m);
    js_declare_GuiStyleProp(ctx, m);

    JS_SetModuleExport(ctx, m, "FLAG_VSYNC_HINT", JS_NewInt32(ctx, FLAG_VSYNC_HINT));
    JS_SetModuleExport(ctx, m, "FLAG_FULLSCREEN_MODE", JS_NewInt32(ctx, FLAG_FULLSCREEN_MODE));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_RESIZABLE", JS_NewInt32(ctx, FLAG_WINDOW_RESIZABLE));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_UNDECORATED", JS_NewInt32(ctx, FLAG_WINDOW_UNDECORATED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_HIDDEN", JS_NewInt32(ctx, FLAG_WINDOW_HIDDEN));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_MINIMIZED", JS_NewInt32(ctx, FLAG_WINDOW_MINIMIZED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_MAXIMIZED", JS_NewInt32(ctx, FLAG_WINDOW_MAXIMIZED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_UNFOCUSED", JS_NewInt32(ctx, FLAG_WINDOW_UNFOCUSED));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_TOPMOST", JS_NewInt32(ctx, FLAG_WINDOW_TOPMOST));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_ALWAYS_RUN", JS_NewInt32(ctx, FLAG_WINDOW_ALWAYS_RUN));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_TRANSPARENT", JS_NewInt32(ctx, FLAG_WINDOW_TRANSPARENT));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_HIGHDPI", JS_NewInt32(ctx, FLAG_WINDOW_HIGHDPI));
    JS_SetModuleExport(ctx, m, "FLAG_WINDOW_MOUSE_PASSTHROUGH", JS_NewInt32(ctx, FLAG_WINDOW_MOUSE_PASSTHROUGH));
    JS_SetModuleExport(ctx, m, "FLAG_BORDERLESS_WINDOWED_MODE", JS_NewInt32(ctx, FLAG_BORDERLESS_WINDOWED_MODE));
    JS_SetModuleExport(ctx, m, "FLAG_MSAA_4X_HINT", JS_NewInt32(ctx, FLAG_MSAA_4X_HINT));
    JS_SetModuleExport(ctx, m, "FLAG_INTERLACED_HINT", JS_NewInt32(ctx, FLAG_INTERLACED_HINT));
    JS_SetModuleExport(ctx, m, "LOG_ALL", JS_NewInt32(ctx, LOG_ALL));
    JS_SetModuleExport(ctx, m, "LOG_TRACE", JS_NewInt32(ctx, LOG_TRACE));
    JS_SetModuleExport(ctx, m, "LOG_DEBUG", JS_NewInt32(ctx, LOG_DEBUG));
    JS_SetModuleExport(ctx, m, "LOG_INFO", JS_NewInt32(ctx, LOG_INFO));
    JS_SetModuleExport(ctx, m, "LOG_WARNING", JS_NewInt32(ctx, LOG_WARNING));
    JS_SetModuleExport(ctx, m, "LOG_ERROR", JS_NewInt32(ctx, LOG_ERROR));
    JS_SetModuleExport(ctx, m, "LOG_FATAL", JS_NewInt32(ctx, LOG_FATAL));
    JS_SetModuleExport(ctx, m, "LOG_NONE", JS_NewInt32(ctx, LOG_NONE));
    JS_SetModuleExport(ctx, m, "KEY_NULL", JS_NewInt32(ctx, KEY_NULL));
    JS_SetModuleExport(ctx, m, "KEY_APOSTROPHE", JS_NewInt32(ctx, KEY_APOSTROPHE));
    JS_SetModuleExport(ctx, m, "KEY_COMMA", JS_NewInt32(ctx, KEY_COMMA));
    JS_SetModuleExport(ctx, m, "KEY_MINUS", JS_NewInt32(ctx, KEY_MINUS));
    JS_SetModuleExport(ctx, m, "KEY_PERIOD", JS_NewInt32(ctx, KEY_PERIOD));
    JS_SetModuleExport(ctx, m, "KEY_SLASH", JS_NewInt32(ctx, KEY_SLASH));
    JS_SetModuleExport(ctx, m, "KEY_ZERO", JS_NewInt32(ctx, KEY_ZERO));
    JS_SetModuleExport(ctx, m, "KEY_ONE", JS_NewInt32(ctx, KEY_ONE));
    JS_SetModuleExport(ctx, m, "KEY_TWO", JS_NewInt32(ctx, KEY_TWO));
    JS_SetModuleExport(ctx, m, "KEY_THREE", JS_NewInt32(ctx, KEY_THREE));
    JS_SetModuleExport(ctx, m, "KEY_FOUR", JS_NewInt32(ctx, KEY_FOUR));
    JS_SetModuleExport(ctx, m, "KEY_FIVE", JS_NewInt32(ctx, KEY_FIVE));
    JS_SetModuleExport(ctx, m, "KEY_SIX", JS_NewInt32(ctx, KEY_SIX));
    JS_SetModuleExport(ctx, m, "KEY_SEVEN", JS_NewInt32(ctx, KEY_SEVEN));
    JS_SetModuleExport(ctx, m, "KEY_EIGHT", JS_NewInt32(ctx, KEY_EIGHT));
    JS_SetModuleExport(ctx, m, "KEY_NINE", JS_NewInt32(ctx, KEY_NINE));
    JS_SetModuleExport(ctx, m, "KEY_SEMICOLON", JS_NewInt32(ctx, KEY_SEMICOLON));
    JS_SetModuleExport(ctx, m, "KEY_EQUAL", JS_NewInt32(ctx, KEY_EQUAL));
    JS_SetModuleExport(ctx, m, "KEY_A", JS_NewInt32(ctx, KEY_A));
    JS_SetModuleExport(ctx, m, "KEY_B", JS_NewInt32(ctx, KEY_B));
    JS_SetModuleExport(ctx, m, "KEY_C", JS_NewInt32(ctx, KEY_C));
    JS_SetModuleExport(ctx, m, "KEY_D", JS_NewInt32(ctx, KEY_D));
    JS_SetModuleExport(ctx, m, "KEY_E", JS_NewInt32(ctx, KEY_E));
    JS_SetModuleExport(ctx, m, "KEY_F", JS_NewInt32(ctx, KEY_F));
    JS_SetModuleExport(ctx, m, "KEY_G", JS_NewInt32(ctx, KEY_G));
    JS_SetModuleExport(ctx, m, "KEY_H", JS_NewInt32(ctx, KEY_H));
    JS_SetModuleExport(ctx, m, "KEY_I", JS_NewInt32(ctx, KEY_I));
    JS_SetModuleExport(ctx, m, "KEY_J", JS_NewInt32(ctx, KEY_J));
    JS_SetModuleExport(ctx, m, "KEY_K", JS_NewInt32(ctx, KEY_K));
    JS_SetModuleExport(ctx, m, "KEY_L", JS_NewInt32(ctx, KEY_L));
    JS_SetModuleExport(ctx, m, "KEY_M", JS_NewInt32(ctx, KEY_M));
    JS_SetModuleExport(ctx, m, "KEY_N", JS_NewInt32(ctx, KEY_N));
    JS_SetModuleExport(ctx, m, "KEY_O", JS_NewInt32(ctx, KEY_O));
    JS_SetModuleExport(ctx, m, "KEY_P", JS_NewInt32(ctx, KEY_P));
    JS_SetModuleExport(ctx, m, "KEY_Q", JS_NewInt32(ctx, KEY_Q));
    JS_SetModuleExport(ctx, m, "KEY_R", JS_NewInt32(ctx, KEY_R));
    JS_SetModuleExport(ctx, m, "KEY_S", JS_NewInt32(ctx, KEY_S));
    JS_SetModuleExport(ctx, m, "KEY_T", JS_NewInt32(ctx, KEY_T));
    JS_SetModuleExport(ctx, m, "KEY_U", JS_NewInt32(ctx, KEY_U));
    JS_SetModuleExport(ctx, m, "KEY_V", JS_NewInt32(ctx, KEY_V));
    JS_SetModuleExport(ctx, m, "KEY_W", JS_NewInt32(ctx, KEY_W));
    JS_SetModuleExport(ctx, m, "KEY_X", JS_NewInt32(ctx, KEY_X));
    JS_SetModuleExport(ctx, m, "KEY_Y", JS_NewInt32(ctx, KEY_Y));
    JS_SetModuleExport(ctx, m, "KEY_Z", JS_NewInt32(ctx, KEY_Z));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_BRACKET", JS_NewInt32(ctx, KEY_LEFT_BRACKET));
    JS_SetModuleExport(ctx, m, "KEY_BACKSLASH", JS_NewInt32(ctx, KEY_BACKSLASH));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_BRACKET", JS_NewInt32(ctx, KEY_RIGHT_BRACKET));
    JS_SetModuleExport(ctx, m, "KEY_GRAVE", JS_NewInt32(ctx, KEY_GRAVE));
    JS_SetModuleExport(ctx, m, "KEY_SPACE", JS_NewInt32(ctx, KEY_SPACE));
    JS_SetModuleExport(ctx, m, "KEY_ESCAPE", JS_NewInt32(ctx, KEY_ESCAPE));
    JS_SetModuleExport(ctx, m, "KEY_ENTER", JS_NewInt32(ctx, KEY_ENTER));
    JS_SetModuleExport(ctx, m, "KEY_TAB", JS_NewInt32(ctx, KEY_TAB));
    JS_SetModuleExport(ctx, m, "KEY_BACKSPACE", JS_NewInt32(ctx, KEY_BACKSPACE));
    JS_SetModuleExport(ctx, m, "KEY_INSERT", JS_NewInt32(ctx, KEY_INSERT));
    JS_SetModuleExport(ctx, m, "KEY_DELETE", JS_NewInt32(ctx, KEY_DELETE));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT", JS_NewInt32(ctx, KEY_RIGHT));
    JS_SetModuleExport(ctx, m, "KEY_LEFT", JS_NewInt32(ctx, KEY_LEFT));
    JS_SetModuleExport(ctx, m, "KEY_DOWN", JS_NewInt32(ctx, KEY_DOWN));
    JS_SetModuleExport(ctx, m, "KEY_UP", JS_NewInt32(ctx, KEY_UP));
    JS_SetModuleExport(ctx, m, "KEY_PAGE_UP", JS_NewInt32(ctx, KEY_PAGE_UP));
    JS_SetModuleExport(ctx, m, "KEY_PAGE_DOWN", JS_NewInt32(ctx, KEY_PAGE_DOWN));
    JS_SetModuleExport(ctx, m, "KEY_HOME", JS_NewInt32(ctx, KEY_HOME));
    JS_SetModuleExport(ctx, m, "KEY_END", JS_NewInt32(ctx, KEY_END));
    JS_SetModuleExport(ctx, m, "KEY_CAPS_LOCK", JS_NewInt32(ctx, KEY_CAPS_LOCK));
    JS_SetModuleExport(ctx, m, "KEY_SCROLL_LOCK", JS_NewInt32(ctx, KEY_SCROLL_LOCK));
    JS_SetModuleExport(ctx, m, "KEY_NUM_LOCK", JS_NewInt32(ctx, KEY_NUM_LOCK));
    JS_SetModuleExport(ctx, m, "KEY_PRINT_SCREEN", JS_NewInt32(ctx, KEY_PRINT_SCREEN));
    JS_SetModuleExport(ctx, m, "KEY_PAUSE", JS_NewInt32(ctx, KEY_PAUSE));
    JS_SetModuleExport(ctx, m, "KEY_F1", JS_NewInt32(ctx, KEY_F1));
    JS_SetModuleExport(ctx, m, "KEY_F2", JS_NewInt32(ctx, KEY_F2));
    JS_SetModuleExport(ctx, m, "KEY_F3", JS_NewInt32(ctx, KEY_F3));
    JS_SetModuleExport(ctx, m, "KEY_F4", JS_NewInt32(ctx, KEY_F4));
    JS_SetModuleExport(ctx, m, "KEY_F5", JS_NewInt32(ctx, KEY_F5));
    JS_SetModuleExport(ctx, m, "KEY_F6", JS_NewInt32(ctx, KEY_F6));
    JS_SetModuleExport(ctx, m, "KEY_F7", JS_NewInt32(ctx, KEY_F7));
    JS_SetModuleExport(ctx, m, "KEY_F8", JS_NewInt32(ctx, KEY_F8));
    JS_SetModuleExport(ctx, m, "KEY_F9", JS_NewInt32(ctx, KEY_F9));
    JS_SetModuleExport(ctx, m, "KEY_F10", JS_NewInt32(ctx, KEY_F10));
    JS_SetModuleExport(ctx, m, "KEY_F11", JS_NewInt32(ctx, KEY_F11));
    JS_SetModuleExport(ctx, m, "KEY_F12", JS_NewInt32(ctx, KEY_F12));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_SHIFT", JS_NewInt32(ctx, KEY_LEFT_SHIFT));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_CONTROL", JS_NewInt32(ctx, KEY_LEFT_CONTROL));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_ALT", JS_NewInt32(ctx, KEY_LEFT_ALT));
    JS_SetModuleExport(ctx, m, "KEY_LEFT_SUPER", JS_NewInt32(ctx, KEY_LEFT_SUPER));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_SHIFT", JS_NewInt32(ctx, KEY_RIGHT_SHIFT));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_CONTROL", JS_NewInt32(ctx, KEY_RIGHT_CONTROL));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_ALT", JS_NewInt32(ctx, KEY_RIGHT_ALT));
    JS_SetModuleExport(ctx, m, "KEY_RIGHT_SUPER", JS_NewInt32(ctx, KEY_RIGHT_SUPER));
    JS_SetModuleExport(ctx, m, "KEY_KB_MENU", JS_NewInt32(ctx, KEY_KB_MENU));
    JS_SetModuleExport(ctx, m, "KEY_KP_0", JS_NewInt32(ctx, KEY_KP_0));
    JS_SetModuleExport(ctx, m, "KEY_KP_1", JS_NewInt32(ctx, KEY_KP_1));
    JS_SetModuleExport(ctx, m, "KEY_KP_2", JS_NewInt32(ctx, KEY_KP_2));
    JS_SetModuleExport(ctx, m, "KEY_KP_3", JS_NewInt32(ctx, KEY_KP_3));
    JS_SetModuleExport(ctx, m, "KEY_KP_4", JS_NewInt32(ctx, KEY_KP_4));
    JS_SetModuleExport(ctx, m, "KEY_KP_5", JS_NewInt32(ctx, KEY_KP_5));
    JS_SetModuleExport(ctx, m, "KEY_KP_6", JS_NewInt32(ctx, KEY_KP_6));
    JS_SetModuleExport(ctx, m, "KEY_KP_7", JS_NewInt32(ctx, KEY_KP_7));
    JS_SetModuleExport(ctx, m, "KEY_KP_8", JS_NewInt32(ctx, KEY_KP_8));
    JS_SetModuleExport(ctx, m, "KEY_KP_9", JS_NewInt32(ctx, KEY_KP_9));
    JS_SetModuleExport(ctx, m, "KEY_KP_DECIMAL", JS_NewInt32(ctx, KEY_KP_DECIMAL));
    JS_SetModuleExport(ctx, m, "KEY_KP_DIVIDE", JS_NewInt32(ctx, KEY_KP_DIVIDE));
    JS_SetModuleExport(ctx, m, "KEY_KP_MULTIPLY", JS_NewInt32(ctx, KEY_KP_MULTIPLY));
    JS_SetModuleExport(ctx, m, "KEY_KP_SUBTRACT", JS_NewInt32(ctx, KEY_KP_SUBTRACT));
    JS_SetModuleExport(ctx, m, "KEY_KP_ADD", JS_NewInt32(ctx, KEY_KP_ADD));
    JS_SetModuleExport(ctx, m, "KEY_KP_ENTER", JS_NewInt32(ctx, KEY_KP_ENTER));
    JS_SetModuleExport(ctx, m, "KEY_KP_EQUAL", JS_NewInt32(ctx, KEY_KP_EQUAL));
    JS_SetModuleExport(ctx, m, "KEY_BACK", JS_NewInt32(ctx, KEY_BACK));
    JS_SetModuleExport(ctx, m, "KEY_MENU", JS_NewInt32(ctx, KEY_MENU));
    JS_SetModuleExport(ctx, m, "KEY_VOLUME_UP", JS_NewInt32(ctx, KEY_VOLUME_UP));
    JS_SetModuleExport(ctx, m, "KEY_VOLUME_DOWN", JS_NewInt32(ctx, KEY_VOLUME_DOWN));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_LEFT", JS_NewInt32(ctx, MOUSE_BUTTON_LEFT));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_RIGHT", JS_NewInt32(ctx, MOUSE_BUTTON_RIGHT));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_MIDDLE", JS_NewInt32(ctx, MOUSE_BUTTON_MIDDLE));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_SIDE", JS_NewInt32(ctx, MOUSE_BUTTON_SIDE));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_EXTRA", JS_NewInt32(ctx, MOUSE_BUTTON_EXTRA));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_FORWARD", JS_NewInt32(ctx, MOUSE_BUTTON_FORWARD));
    JS_SetModuleExport(ctx, m, "MOUSE_BUTTON_BACK", JS_NewInt32(ctx, MOUSE_BUTTON_BACK));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_DEFAULT", JS_NewInt32(ctx, MOUSE_CURSOR_DEFAULT));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_ARROW", JS_NewInt32(ctx, MOUSE_CURSOR_ARROW));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_IBEAM", JS_NewInt32(ctx, MOUSE_CURSOR_IBEAM));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_CROSSHAIR", JS_NewInt32(ctx, MOUSE_CURSOR_CROSSHAIR));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_POINTING_HAND", JS_NewInt32(ctx, MOUSE_CURSOR_POINTING_HAND));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_EW", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_EW));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NS", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_NS));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NWSE", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_NWSE));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NESW", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_NESW));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_ALL", JS_NewInt32(ctx, MOUSE_CURSOR_RESIZE_ALL));
    JS_SetModuleExport(ctx, m, "MOUSE_CURSOR_NOT_ALLOWED", JS_NewInt32(ctx, MOUSE_CURSOR_NOT_ALLOWED));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_UNKNOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_UNKNOWN));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_UP", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_UP));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_RIGHT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_DOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_DOWN));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_FACE_LEFT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_UP", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_UP));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_DOWN));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_FACE_LEFT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_1", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_TRIGGER_1));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_2", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_TRIGGER_2));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_TRIGGER_1));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_TRIGGER_2));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_LEFT", JS_NewInt32(ctx, GAMEPAD_BUTTON_MIDDLE_LEFT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE", JS_NewInt32(ctx, GAMEPAD_BUTTON_MIDDLE));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_RIGHT", JS_NewInt32(ctx, GAMEPAD_BUTTON_MIDDLE_RIGHT));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_THUMB", JS_NewInt32(ctx, GAMEPAD_BUTTON_LEFT_THUMB));
    JS_SetModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_THUMB", JS_NewInt32(ctx, GAMEPAD_BUTTON_RIGHT_THUMB));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_X", JS_NewInt32(ctx, GAMEPAD_AXIS_LEFT_X));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_Y", JS_NewInt32(ctx, GAMEPAD_AXIS_LEFT_Y));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_X", JS_NewInt32(ctx, GAMEPAD_AXIS_RIGHT_X));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_Y", JS_NewInt32(ctx, GAMEPAD_AXIS_RIGHT_Y));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_TRIGGER", JS_NewInt32(ctx, GAMEPAD_AXIS_LEFT_TRIGGER));
    JS_SetModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_TRIGGER", JS_NewInt32(ctx, GAMEPAD_AXIS_RIGHT_TRIGGER));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_ALBEDO", JS_NewInt32(ctx, MATERIAL_MAP_ALBEDO));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_METALNESS", JS_NewInt32(ctx, MATERIAL_MAP_METALNESS));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_NORMAL", JS_NewInt32(ctx, MATERIAL_MAP_NORMAL));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_ROUGHNESS", JS_NewInt32(ctx, MATERIAL_MAP_ROUGHNESS));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_OCCLUSION", JS_NewInt32(ctx, MATERIAL_MAP_OCCLUSION));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_EMISSION", JS_NewInt32(ctx, MATERIAL_MAP_EMISSION));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_HEIGHT", JS_NewInt32(ctx, MATERIAL_MAP_HEIGHT));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_CUBEMAP", JS_NewInt32(ctx, MATERIAL_MAP_CUBEMAP));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_IRRADIANCE", JS_NewInt32(ctx, MATERIAL_MAP_IRRADIANCE));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_PREFILTER", JS_NewInt32(ctx, MATERIAL_MAP_PREFILTER));
    JS_SetModuleExport(ctx, m, "MATERIAL_MAP_BRDF", JS_NewInt32(ctx, MATERIAL_MAP_BRDF));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_POSITION", JS_NewInt32(ctx, SHADER_LOC_VERTEX_POSITION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD01", JS_NewInt32(ctx, SHADER_LOC_VERTEX_TEXCOORD01));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD02", JS_NewInt32(ctx, SHADER_LOC_VERTEX_TEXCOORD02));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_NORMAL", JS_NewInt32(ctx, SHADER_LOC_VERTEX_NORMAL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_TANGENT", JS_NewInt32(ctx, SHADER_LOC_VERTEX_TANGENT));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VERTEX_COLOR", JS_NewInt32(ctx, SHADER_LOC_VERTEX_COLOR));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_MVP", JS_NewInt32(ctx, SHADER_LOC_MATRIX_MVP));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_VIEW", JS_NewInt32(ctx, SHADER_LOC_MATRIX_VIEW));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_PROJECTION", JS_NewInt32(ctx, SHADER_LOC_MATRIX_PROJECTION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_MODEL", JS_NewInt32(ctx, SHADER_LOC_MATRIX_MODEL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MATRIX_NORMAL", JS_NewInt32(ctx, SHADER_LOC_MATRIX_NORMAL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_VECTOR_VIEW", JS_NewInt32(ctx, SHADER_LOC_VECTOR_VIEW));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_COLOR_DIFFUSE", JS_NewInt32(ctx, SHADER_LOC_COLOR_DIFFUSE));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_COLOR_SPECULAR", JS_NewInt32(ctx, SHADER_LOC_COLOR_SPECULAR));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_COLOR_AMBIENT", JS_NewInt32(ctx, SHADER_LOC_COLOR_AMBIENT));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_ALBEDO", JS_NewInt32(ctx, SHADER_LOC_MAP_ALBEDO));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_METALNESS", JS_NewInt32(ctx, SHADER_LOC_MAP_METALNESS));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_NORMAL", JS_NewInt32(ctx, SHADER_LOC_MAP_NORMAL));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_ROUGHNESS", JS_NewInt32(ctx, SHADER_LOC_MAP_ROUGHNESS));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_OCCLUSION", JS_NewInt32(ctx, SHADER_LOC_MAP_OCCLUSION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_EMISSION", JS_NewInt32(ctx, SHADER_LOC_MAP_EMISSION));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_HEIGHT", JS_NewInt32(ctx, SHADER_LOC_MAP_HEIGHT));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_CUBEMAP", JS_NewInt32(ctx, SHADER_LOC_MAP_CUBEMAP));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_IRRADIANCE", JS_NewInt32(ctx, SHADER_LOC_MAP_IRRADIANCE));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_PREFILTER", JS_NewInt32(ctx, SHADER_LOC_MAP_PREFILTER));
    JS_SetModuleExport(ctx, m, "SHADER_LOC_MAP_BRDF", JS_NewInt32(ctx, SHADER_LOC_MAP_BRDF));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_FLOAT", JS_NewInt32(ctx, SHADER_UNIFORM_FLOAT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC2", JS_NewInt32(ctx, SHADER_UNIFORM_VEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC3", JS_NewInt32(ctx, SHADER_UNIFORM_VEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_VEC4", JS_NewInt32(ctx, SHADER_UNIFORM_VEC4));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_INT", JS_NewInt32(ctx, SHADER_UNIFORM_INT));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC2", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC2));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC3", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC3));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_IVEC4", JS_NewInt32(ctx, SHADER_UNIFORM_IVEC4));
    JS_SetModuleExport(ctx, m, "SHADER_UNIFORM_SAMPLER2D", JS_NewInt32(ctx, SHADER_UNIFORM_SAMPLER2D));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_FLOAT", JS_NewInt32(ctx, SHADER_ATTRIB_FLOAT));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_VEC2", JS_NewInt32(ctx, SHADER_ATTRIB_VEC2));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_VEC3", JS_NewInt32(ctx, SHADER_ATTRIB_VEC3));
    JS_SetModuleExport(ctx, m, "SHADER_ATTRIB_VEC4", JS_NewInt32(ctx, SHADER_ATTRIB_VEC4));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G6B5", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R5G6B5));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R8G8B8));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R5G5B5A1));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R4G4B4A4));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R32));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R32G32B32));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R32G32B32A32));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R16));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R16G16B16));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16A16", JS_NewInt32(ctx, PIXELFORMAT_UNCOMPRESSED_R16G16B16A16));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT1_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT1_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT3_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT3_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT5_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_DXT5_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC1_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ETC1_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ETC2_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGB", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_PVRT_RGB));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_PVRT_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA));
    JS_SetModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA", JS_NewInt32(ctx, PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_POINT", JS_NewInt32(ctx, TEXTURE_FILTER_POINT));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_BILINEAR", JS_NewInt32(ctx, TEXTURE_FILTER_BILINEAR));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_TRILINEAR", JS_NewInt32(ctx, TEXTURE_FILTER_TRILINEAR));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_4X", JS_NewInt32(ctx, TEXTURE_FILTER_ANISOTROPIC_4X));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_8X", JS_NewInt32(ctx, TEXTURE_FILTER_ANISOTROPIC_8X));
    JS_SetModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_16X", JS_NewInt32(ctx, TEXTURE_FILTER_ANISOTROPIC_16X));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_REPEAT", JS_NewInt32(ctx, TEXTURE_WRAP_REPEAT));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_CLAMP", JS_NewInt32(ctx, TEXTURE_WRAP_CLAMP));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_REPEAT", JS_NewInt32(ctx, TEXTURE_WRAP_MIRROR_REPEAT));
    JS_SetModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_CLAMP", JS_NewInt32(ctx, TEXTURE_WRAP_MIRROR_CLAMP));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_AUTO_DETECT", JS_NewInt32(ctx, CUBEMAP_LAYOUT_AUTO_DETECT));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_VERTICAL", JS_NewInt32(ctx, CUBEMAP_LAYOUT_LINE_VERTICAL));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_HORIZONTAL", JS_NewInt32(ctx, CUBEMAP_LAYOUT_LINE_HORIZONTAL));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR", JS_NewInt32(ctx, CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE", JS_NewInt32(ctx, CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE));
    JS_SetModuleExport(ctx, m, "CUBEMAP_LAYOUT_PANORAMA", JS_NewInt32(ctx, CUBEMAP_LAYOUT_PANORAMA));
    JS_SetModuleExport(ctx, m, "FONT_DEFAULT", JS_NewInt32(ctx, FONT_DEFAULT));
    JS_SetModuleExport(ctx, m, "FONT_BITMAP", JS_NewInt32(ctx, FONT_BITMAP));
    JS_SetModuleExport(ctx, m, "FONT_SDF", JS_NewInt32(ctx, FONT_SDF));
    JS_SetModuleExport(ctx, m, "BLEND_ALPHA", JS_NewInt32(ctx, BLEND_ALPHA));
    JS_SetModuleExport(ctx, m, "BLEND_ADDITIVE", JS_NewInt32(ctx, BLEND_ADDITIVE));
    JS_SetModuleExport(ctx, m, "BLEND_MULTIPLIED", JS_NewInt32(ctx, BLEND_MULTIPLIED));
    JS_SetModuleExport(ctx, m, "BLEND_ADD_COLORS", JS_NewInt32(ctx, BLEND_ADD_COLORS));
    JS_SetModuleExport(ctx, m, "BLEND_SUBTRACT_COLORS", JS_NewInt32(ctx, BLEND_SUBTRACT_COLORS));
    JS_SetModuleExport(ctx, m, "BLEND_ALPHA_PREMULTIPLY", JS_NewInt32(ctx, BLEND_ALPHA_PREMULTIPLY));
    JS_SetModuleExport(ctx, m, "BLEND_CUSTOM", JS_NewInt32(ctx, BLEND_CUSTOM));
    JS_SetModuleExport(ctx, m, "BLEND_CUSTOM_SEPARATE", JS_NewInt32(ctx, BLEND_CUSTOM_SEPARATE));
    JS_SetModuleExport(ctx, m, "GESTURE_NONE", JS_NewInt32(ctx, GESTURE_NONE));
    JS_SetModuleExport(ctx, m, "GESTURE_TAP", JS_NewInt32(ctx, GESTURE_TAP));
    JS_SetModuleExport(ctx, m, "GESTURE_DOUBLETAP", JS_NewInt32(ctx, GESTURE_DOUBLETAP));
    JS_SetModuleExport(ctx, m, "GESTURE_HOLD", JS_NewInt32(ctx, GESTURE_HOLD));
    JS_SetModuleExport(ctx, m, "GESTURE_DRAG", JS_NewInt32(ctx, GESTURE_DRAG));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_RIGHT", JS_NewInt32(ctx, GESTURE_SWIPE_RIGHT));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_LEFT", JS_NewInt32(ctx, GESTURE_SWIPE_LEFT));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_UP", JS_NewInt32(ctx, GESTURE_SWIPE_UP));
    JS_SetModuleExport(ctx, m, "GESTURE_SWIPE_DOWN", JS_NewInt32(ctx, GESTURE_SWIPE_DOWN));
    JS_SetModuleExport(ctx, m, "GESTURE_PINCH_IN", JS_NewInt32(ctx, GESTURE_PINCH_IN));
    JS_SetModuleExport(ctx, m, "GESTURE_PINCH_OUT", JS_NewInt32(ctx, GESTURE_PINCH_OUT));
    JS_SetModuleExport(ctx, m, "CAMERA_CUSTOM", JS_NewInt32(ctx, CAMERA_CUSTOM));
    JS_SetModuleExport(ctx, m, "CAMERA_FREE", JS_NewInt32(ctx, CAMERA_FREE));
    JS_SetModuleExport(ctx, m, "CAMERA_ORBITAL", JS_NewInt32(ctx, CAMERA_ORBITAL));
    JS_SetModuleExport(ctx, m, "CAMERA_FIRST_PERSON", JS_NewInt32(ctx, CAMERA_FIRST_PERSON));
    JS_SetModuleExport(ctx, m, "CAMERA_THIRD_PERSON", JS_NewInt32(ctx, CAMERA_THIRD_PERSON));
    JS_SetModuleExport(ctx, m, "CAMERA_PERSPECTIVE", JS_NewInt32(ctx, CAMERA_PERSPECTIVE));
    JS_SetModuleExport(ctx, m, "CAMERA_ORTHOGRAPHIC", JS_NewInt32(ctx, CAMERA_ORTHOGRAPHIC));
    JS_SetModuleExport(ctx, m, "NPATCH_NINE_PATCH", JS_NewInt32(ctx, NPATCH_NINE_PATCH));
    JS_SetModuleExport(ctx, m, "NPATCH_THREE_PATCH_VERTICAL", JS_NewInt32(ctx, NPATCH_THREE_PATCH_VERTICAL));
    JS_SetModuleExport(ctx, m, "NPATCH_THREE_PATCH_HORIZONTAL", JS_NewInt32(ctx, NPATCH_THREE_PATCH_HORIZONTAL));
    JS_SetModuleExport(ctx, m, "CAMERA_PERSPECTIVE", JS_NewInt32(ctx, CAMERA_PERSPECTIVE));
    JS_SetModuleExport(ctx, m, "CAMERA_ORTHOGRAPHIC", JS_NewInt32(ctx, CAMERA_ORTHOGRAPHIC));
    JS_SetModuleExport(ctx, m, "CAMERA_CUSTOM", JS_NewInt32(ctx, CAMERA_CUSTOM));
    JS_SetModuleExport(ctx, m, "CAMERA_FREE", JS_NewInt32(ctx, CAMERA_FREE));
    JS_SetModuleExport(ctx, m, "CAMERA_ORBITAL", JS_NewInt32(ctx, CAMERA_ORBITAL));
    JS_SetModuleExport(ctx, m, "CAMERA_FIRST_PERSON", JS_NewInt32(ctx, CAMERA_FIRST_PERSON));
    JS_SetModuleExport(ctx, m, "CAMERA_THIRD_PERSON", JS_NewInt32(ctx, CAMERA_THIRD_PERSON));
    JS_SetModuleExport(ctx, m, "STATE_NORMAL", JS_NewInt32(ctx, STATE_NORMAL));
    JS_SetModuleExport(ctx, m, "STATE_FOCUSED", JS_NewInt32(ctx, STATE_FOCUSED));
    JS_SetModuleExport(ctx, m, "STATE_PRESSED", JS_NewInt32(ctx, STATE_PRESSED));
    JS_SetModuleExport(ctx, m, "STATE_DISABLED", JS_NewInt32(ctx, STATE_DISABLED));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_LEFT", JS_NewInt32(ctx, TEXT_ALIGN_LEFT));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_CENTER", JS_NewInt32(ctx, TEXT_ALIGN_CENTER));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_RIGHT", JS_NewInt32(ctx, TEXT_ALIGN_RIGHT));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_TOP", JS_NewInt32(ctx, TEXT_ALIGN_TOP));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_MIDDLE", JS_NewInt32(ctx, TEXT_ALIGN_MIDDLE));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGN_BOTTOM", JS_NewInt32(ctx, TEXT_ALIGN_BOTTOM));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_NONE", JS_NewInt32(ctx, TEXT_WRAP_NONE));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_CHAR", JS_NewInt32(ctx, TEXT_WRAP_CHAR));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_WORD", JS_NewInt32(ctx, TEXT_WRAP_WORD));
    JS_SetModuleExport(ctx, m, "DEFAULT", JS_NewInt32(ctx, DEFAULT));
    JS_SetModuleExport(ctx, m, "LABEL", JS_NewInt32(ctx, LABEL));
    JS_SetModuleExport(ctx, m, "BUTTON", JS_NewInt32(ctx, BUTTON));
    JS_SetModuleExport(ctx, m, "TOGGLE", JS_NewInt32(ctx, TOGGLE));
    JS_SetModuleExport(ctx, m, "SLIDER", JS_NewInt32(ctx, SLIDER));
    JS_SetModuleExport(ctx, m, "PROGRESSBAR", JS_NewInt32(ctx, PROGRESSBAR));
    JS_SetModuleExport(ctx, m, "CHECKBOX", JS_NewInt32(ctx, CHECKBOX));
    JS_SetModuleExport(ctx, m, "COMBOBOX", JS_NewInt32(ctx, COMBOBOX));
    JS_SetModuleExport(ctx, m, "DROPDOWNBOX", JS_NewInt32(ctx, DROPDOWNBOX));
    JS_SetModuleExport(ctx, m, "TEXTBOX", JS_NewInt32(ctx, TEXTBOX));
    JS_SetModuleExport(ctx, m, "VALUEBOX", JS_NewInt32(ctx, VALUEBOX));
    JS_SetModuleExport(ctx, m, "SPINNER", JS_NewInt32(ctx, SPINNER));
    JS_SetModuleExport(ctx, m, "LISTVIEW", JS_NewInt32(ctx, LISTVIEW));
    JS_SetModuleExport(ctx, m, "COLORPICKER", JS_NewInt32(ctx, COLORPICKER));
    JS_SetModuleExport(ctx, m, "SCROLLBAR", JS_NewInt32(ctx, SCROLLBAR));
    JS_SetModuleExport(ctx, m, "STATUSBAR", JS_NewInt32(ctx, STATUSBAR));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_NORMAL", JS_NewInt32(ctx, BORDER_COLOR_NORMAL));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_NORMAL", JS_NewInt32(ctx, BASE_COLOR_NORMAL));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_NORMAL", JS_NewInt32(ctx, TEXT_COLOR_NORMAL));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_FOCUSED", JS_NewInt32(ctx, BORDER_COLOR_FOCUSED));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_FOCUSED", JS_NewInt32(ctx, BASE_COLOR_FOCUSED));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_FOCUSED", JS_NewInt32(ctx, TEXT_COLOR_FOCUSED));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_PRESSED", JS_NewInt32(ctx, BORDER_COLOR_PRESSED));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_PRESSED", JS_NewInt32(ctx, BASE_COLOR_PRESSED));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_PRESSED", JS_NewInt32(ctx, TEXT_COLOR_PRESSED));
    JS_SetModuleExport(ctx, m, "BORDER_COLOR_DISABLED", JS_NewInt32(ctx, BORDER_COLOR_DISABLED));
    JS_SetModuleExport(ctx, m, "BASE_COLOR_DISABLED", JS_NewInt32(ctx, BASE_COLOR_DISABLED));
    JS_SetModuleExport(ctx, m, "TEXT_COLOR_DISABLED", JS_NewInt32(ctx, TEXT_COLOR_DISABLED));
    JS_SetModuleExport(ctx, m, "BORDER_WIDTH", JS_NewInt32(ctx, BORDER_WIDTH));
    JS_SetModuleExport(ctx, m, "TEXT_PADDING", JS_NewInt32(ctx, TEXT_PADDING));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGNMENT", JS_NewInt32(ctx, TEXT_ALIGNMENT));
    JS_SetModuleExport(ctx, m, "TEXT_SIZE", JS_NewInt32(ctx, TEXT_SIZE));
    JS_SetModuleExport(ctx, m, "TEXT_SPACING", JS_NewInt32(ctx, TEXT_SPACING));
    JS_SetModuleExport(ctx, m, "LINE_COLOR", JS_NewInt32(ctx, LINE_COLOR));
    JS_SetModuleExport(ctx, m, "BACKGROUND_COLOR", JS_NewInt32(ctx, BACKGROUND_COLOR));
    JS_SetModuleExport(ctx, m, "TEXT_LINE_SPACING", JS_NewInt32(ctx, TEXT_LINE_SPACING));
    JS_SetModuleExport(ctx, m, "TEXT_ALIGNMENT_VERTICAL", JS_NewInt32(ctx, TEXT_ALIGNMENT_VERTICAL));
    JS_SetModuleExport(ctx, m, "TEXT_WRAP_MODE", JS_NewInt32(ctx, TEXT_WRAP_MODE));
    JS_SetModuleExport(ctx, m, "GROUP_PADDING", JS_NewInt32(ctx, GROUP_PADDING));
    JS_SetModuleExport(ctx, m, "SLIDER_WIDTH", JS_NewInt32(ctx, SLIDER_WIDTH));
    JS_SetModuleExport(ctx, m, "SLIDER_PADDING", JS_NewInt32(ctx, SLIDER_PADDING));
    JS_SetModuleExport(ctx, m, "PROGRESS_PADDING", JS_NewInt32(ctx, PROGRESS_PADDING));
    JS_SetModuleExport(ctx, m, "ARROWS_SIZE", JS_NewInt32(ctx, ARROWS_SIZE));
    JS_SetModuleExport(ctx, m, "ARROWS_VISIBLE", JS_NewInt32(ctx, ARROWS_VISIBLE));
    JS_SetModuleExport(ctx, m, "SCROLL_SLIDER_PADDING", JS_NewInt32(ctx, SCROLL_SLIDER_PADDING));
    JS_SetModuleExport(ctx, m, "SCROLL_SLIDER_SIZE", JS_NewInt32(ctx, SCROLL_SLIDER_SIZE));
    JS_SetModuleExport(ctx, m, "SCROLL_PADDING", JS_NewInt32(ctx, SCROLL_PADDING));
    JS_SetModuleExport(ctx, m, "SCROLL_SPEED", JS_NewInt32(ctx, SCROLL_SPEED));
    JS_SetModuleExport(ctx, m, "CHECK_PADDING", JS_NewInt32(ctx, CHECK_PADDING));
    JS_SetModuleExport(ctx, m, "COMBO_BUTTON_WIDTH", JS_NewInt32(ctx, COMBO_BUTTON_WIDTH));
    JS_SetModuleExport(ctx, m, "COMBO_BUTTON_SPACING", JS_NewInt32(ctx, COMBO_BUTTON_SPACING));
    JS_SetModuleExport(ctx, m, "ARROW_PADDING", JS_NewInt32(ctx, ARROW_PADDING));
    JS_SetModuleExport(ctx, m, "DROPDOWN_ITEMS_SPACING", JS_NewInt32(ctx, DROPDOWN_ITEMS_SPACING));
    JS_SetModuleExport(ctx, m, "DROPDOWN_ARROW_HIDDEN", JS_NewInt32(ctx, DROPDOWN_ARROW_HIDDEN));
    JS_SetModuleExport(ctx, m, "DROPDOWN_ROLL_UP", JS_NewInt32(ctx, DROPDOWN_ROLL_UP));
    JS_SetModuleExport(ctx, m, "TEXT_READONLY", JS_NewInt32(ctx, TEXT_READONLY));
    JS_SetModuleExport(ctx, m, "SPIN_BUTTON_WIDTH", JS_NewInt32(ctx, SPIN_BUTTON_WIDTH));
    JS_SetModuleExport(ctx, m, "SPIN_BUTTON_SPACING", JS_NewInt32(ctx, SPIN_BUTTON_SPACING));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_HEIGHT", JS_NewInt32(ctx, LIST_ITEMS_HEIGHT));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_SPACING", JS_NewInt32(ctx, LIST_ITEMS_SPACING));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_WIDTH", JS_NewInt32(ctx, SCROLLBAR_WIDTH));
    JS_SetModuleExport(ctx, m, "SCROLLBAR_SIDE", JS_NewInt32(ctx, SCROLLBAR_SIDE));
    JS_SetModuleExport(ctx, m, "LIST_ITEMS_BORDER_WIDTH", JS_NewInt32(ctx, LIST_ITEMS_BORDER_WIDTH));
    JS_SetModuleExport(ctx, m, "COLOR_SELECTOR_SIZE", JS_NewInt32(ctx, COLOR_SELECTOR_SIZE));
    JS_SetModuleExport(ctx, m, "HUEBAR_WIDTH", JS_NewInt32(ctx, HUEBAR_WIDTH));
    JS_SetModuleExport(ctx, m, "HUEBAR_PADDING", JS_NewInt32(ctx, HUEBAR_PADDING));
    JS_SetModuleExport(ctx, m, "HUEBAR_SELECTOR_HEIGHT", JS_NewInt32(ctx, HUEBAR_SELECTOR_HEIGHT));
    JS_SetModuleExport(ctx, m, "HUEBAR_SELECTOR_OVERFLOW", JS_NewInt32(ctx, HUEBAR_SELECTOR_OVERFLOW));

    Color LIGHTGRAY_struct = {  200, 200, 200, 255  }; 
Color* LIGHTGRAY_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*LIGHTGRAY_js_ptr = LIGHTGRAY_struct;
JSValue LIGHTGRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(LIGHTGRAY_js, LIGHTGRAY_js_ptr);
JS_SetModuleExport(ctx, m, "LIGHTGRAY", LIGHTGRAY_js);
    Color GRAY_struct = {  130, 130, 130, 255  }; 
Color* GRAY_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*GRAY_js_ptr = GRAY_struct;
JSValue GRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(GRAY_js, GRAY_js_ptr);
JS_SetModuleExport(ctx, m, "GRAY", GRAY_js);
    Color DARKGRAY_struct = {  80, 80, 80, 255  }; 
Color* DARKGRAY_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*DARKGRAY_js_ptr = DARKGRAY_struct;
JSValue DARKGRAY_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(DARKGRAY_js, DARKGRAY_js_ptr);
JS_SetModuleExport(ctx, m, "DARKGRAY", DARKGRAY_js);
    Color YELLOW_struct = {  253, 249, 0, 255  }; 
Color* YELLOW_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*YELLOW_js_ptr = YELLOW_struct;
JSValue YELLOW_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(YELLOW_js, YELLOW_js_ptr);
JS_SetModuleExport(ctx, m, "YELLOW", YELLOW_js);
    Color GOLD_struct = {  255, 203, 0, 255  }; 
Color* GOLD_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*GOLD_js_ptr = GOLD_struct;
JSValue GOLD_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(GOLD_js, GOLD_js_ptr);
JS_SetModuleExport(ctx, m, "GOLD", GOLD_js);
    Color ORANGE_struct = {  255, 161, 0, 255  }; 
Color* ORANGE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*ORANGE_js_ptr = ORANGE_struct;
JSValue ORANGE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(ORANGE_js, ORANGE_js_ptr);
JS_SetModuleExport(ctx, m, "ORANGE", ORANGE_js);
    Color PINK_struct = {  255, 109, 194, 255  }; 
Color* PINK_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*PINK_js_ptr = PINK_struct;
JSValue PINK_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(PINK_js, PINK_js_ptr);
JS_SetModuleExport(ctx, m, "PINK", PINK_js);
    Color RED_struct = {  230, 41, 55, 255  }; 
Color* RED_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*RED_js_ptr = RED_struct;
JSValue RED_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(RED_js, RED_js_ptr);
JS_SetModuleExport(ctx, m, "RED", RED_js);
    Color MAROON_struct = {  190, 33, 55, 255  }; 
Color* MAROON_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*MAROON_js_ptr = MAROON_struct;
JSValue MAROON_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(MAROON_js, MAROON_js_ptr);
JS_SetModuleExport(ctx, m, "MAROON", MAROON_js);
    Color GREEN_struct = {  0, 228, 48, 255  }; 
Color* GREEN_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*GREEN_js_ptr = GREEN_struct;
JSValue GREEN_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(GREEN_js, GREEN_js_ptr);
JS_SetModuleExport(ctx, m, "GREEN", GREEN_js);
    Color LIME_struct = {  0, 158, 47, 255  }; 
Color* LIME_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*LIME_js_ptr = LIME_struct;
JSValue LIME_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(LIME_js, LIME_js_ptr);
JS_SetModuleExport(ctx, m, "LIME", LIME_js);
    Color DARKGREEN_struct = {  0, 117, 44, 255  }; 
Color* DARKGREEN_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*DARKGREEN_js_ptr = DARKGREEN_struct;
JSValue DARKGREEN_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(DARKGREEN_js, DARKGREEN_js_ptr);
JS_SetModuleExport(ctx, m, "DARKGREEN", DARKGREEN_js);
    Color SKYBLUE_struct = {  102, 191, 255, 255  }; 
Color* SKYBLUE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*SKYBLUE_js_ptr = SKYBLUE_struct;
JSValue SKYBLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(SKYBLUE_js, SKYBLUE_js_ptr);
JS_SetModuleExport(ctx, m, "SKYBLUE", SKYBLUE_js);
    Color BLUE_struct = {  0, 121, 241, 255  }; 
Color* BLUE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*BLUE_js_ptr = BLUE_struct;
JSValue BLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(BLUE_js, BLUE_js_ptr);
JS_SetModuleExport(ctx, m, "BLUE", BLUE_js);
    Color DARKBLUE_struct = {  0, 82, 172, 255  }; 
Color* DARKBLUE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*DARKBLUE_js_ptr = DARKBLUE_struct;
JSValue DARKBLUE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(DARKBLUE_js, DARKBLUE_js_ptr);
JS_SetModuleExport(ctx, m, "DARKBLUE", DARKBLUE_js);
    Color PURPLE_struct = {  200, 122, 255, 255  }; 
Color* PURPLE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*PURPLE_js_ptr = PURPLE_struct;
JSValue PURPLE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(PURPLE_js, PURPLE_js_ptr);
JS_SetModuleExport(ctx, m, "PURPLE", PURPLE_js);
    Color VIOLET_struct = {  135, 60, 190, 255  }; 
Color* VIOLET_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*VIOLET_js_ptr = VIOLET_struct;
JSValue VIOLET_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(VIOLET_js, VIOLET_js_ptr);
JS_SetModuleExport(ctx, m, "VIOLET", VIOLET_js);
    Color DARKPURPLE_struct = {  112, 31, 126, 255  }; 
Color* DARKPURPLE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*DARKPURPLE_js_ptr = DARKPURPLE_struct;
JSValue DARKPURPLE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(DARKPURPLE_js, DARKPURPLE_js_ptr);
JS_SetModuleExport(ctx, m, "DARKPURPLE", DARKPURPLE_js);
    Color BEIGE_struct = {  211, 176, 131, 255  }; 
Color* BEIGE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*BEIGE_js_ptr = BEIGE_struct;
JSValue BEIGE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(BEIGE_js, BEIGE_js_ptr);
JS_SetModuleExport(ctx, m, "BEIGE", BEIGE_js);
    Color BROWN_struct = {  127, 106, 79, 255  }; 
Color* BROWN_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*BROWN_js_ptr = BROWN_struct;
JSValue BROWN_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(BROWN_js, BROWN_js_ptr);
JS_SetModuleExport(ctx, m, "BROWN", BROWN_js);
    Color DARKBROWN_struct = {  76, 63, 47, 255  }; 
Color* DARKBROWN_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*DARKBROWN_js_ptr = DARKBROWN_struct;
JSValue DARKBROWN_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(DARKBROWN_js, DARKBROWN_js_ptr);
JS_SetModuleExport(ctx, m, "DARKBROWN", DARKBROWN_js);
    Color WHITE_struct = {  255, 255, 255, 255  }; 
Color* WHITE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*WHITE_js_ptr = WHITE_struct;
JSValue WHITE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(WHITE_js, WHITE_js_ptr);
JS_SetModuleExport(ctx, m, "WHITE", WHITE_js);
    Color BLACK_struct = {  0, 0, 0, 255  }; 
Color* BLACK_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*BLACK_js_ptr = BLACK_struct;
JSValue BLACK_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(BLACK_js, BLACK_js_ptr);
JS_SetModuleExport(ctx, m, "BLACK", BLACK_js);
    Color BLANK_struct = {  0, 0, 0, 0  }; 
Color* BLANK_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*BLANK_js_ptr = BLANK_struct;
JSValue BLANK_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(BLANK_js, BLANK_js_ptr);
JS_SetModuleExport(ctx, m, "BLANK", BLANK_js);
    Color MAGENTA_struct = {  255, 0, 255, 255  }; 
Color* MAGENTA_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*MAGENTA_js_ptr = MAGENTA_struct;
JSValue MAGENTA_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(MAGENTA_js, MAGENTA_js_ptr);
JS_SetModuleExport(ctx, m, "MAGENTA", MAGENTA_js);
    Color RAYWHITE_struct = {  245, 245, 245, 255  }; 
Color* RAYWHITE_js_ptr = (Color *)js_malloc(ctx, sizeof(Color));
*RAYWHITE_js_ptr = RAYWHITE_struct;
JSValue RAYWHITE_js = JS_NewObjectClass(ctx, js_Color_class_id);
JS_SetOpaque(RAYWHITE_js, RAYWHITE_js_ptr);
JS_SetModuleExport(ctx, m, "RAYWHITE", RAYWHITE_js);

    return 0;
}
JSModuleDef *js_init_module(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_raylib_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_raylib_funcs, countof(js_raylib_funcs));

    JS_AddModuleExport(ctx, m, "Vector2");
    JS_AddModuleExport(ctx, m, "Vector3");
    JS_AddModuleExport(ctx, m, "Vector4");
    JS_AddModuleExport(ctx, m, "Quaternion");
    JS_AddModuleExport(ctx, m, "Matrix");
    JS_AddModuleExport(ctx, m, "Color");
    JS_AddModuleExport(ctx, m, "Rectangle");
    JS_AddModuleExport(ctx, m, "Image");
    JS_AddModuleExport(ctx, m, "Texture");
    JS_AddModuleExport(ctx, m, "Texture2D");
    JS_AddModuleExport(ctx, m, "TextureCubemap");
    JS_AddModuleExport(ctx, m, "RenderTexture");
    JS_AddModuleExport(ctx, m, "RenderTexture2D");
    JS_AddModuleExport(ctx, m, "NPatchInfo");
    JS_AddModuleExport(ctx, m, "GlyphInfo");
    JS_AddModuleExport(ctx, m, "Font");
    JS_AddModuleExport(ctx, m, "Camera3D");
    JS_AddModuleExport(ctx, m, "Camera");
    JS_AddModuleExport(ctx, m, "Camera2D");
    JS_AddModuleExport(ctx, m, "Mesh");
    JS_AddModuleExport(ctx, m, "Shader");
    JS_AddModuleExport(ctx, m, "MaterialMap");
    JS_AddModuleExport(ctx, m, "Material");
    JS_AddModuleExport(ctx, m, "Transform");
    JS_AddModuleExport(ctx, m, "BoneInfo");
    JS_AddModuleExport(ctx, m, "Model");
    JS_AddModuleExport(ctx, m, "ModelAnimation");
    JS_AddModuleExport(ctx, m, "Ray");
    JS_AddModuleExport(ctx, m, "RayCollision");
    JS_AddModuleExport(ctx, m, "BoundingBox");
    JS_AddModuleExport(ctx, m, "Wave");
    JS_AddModuleExport(ctx, m, "AudioStream");
    JS_AddModuleExport(ctx, m, "Sound");
    JS_AddModuleExport(ctx, m, "Music");
    JS_AddModuleExport(ctx, m, "VrDeviceInfo");
    JS_AddModuleExport(ctx, m, "VrStereoConfig");
    JS_AddModuleExport(ctx, m, "FilePathList");
    JS_AddModuleExport(ctx, m, "AutomationEvent");
    JS_AddModuleExport(ctx, m, "AutomationEventList");
    JS_AddModuleExport(ctx, m, "FLAG_VSYNC_HINT");
    JS_AddModuleExport(ctx, m, "FLAG_FULLSCREEN_MODE");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_RESIZABLE");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_UNDECORATED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_HIDDEN");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_MINIMIZED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_MAXIMIZED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_UNFOCUSED");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_TOPMOST");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_ALWAYS_RUN");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_TRANSPARENT");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_HIGHDPI");
    JS_AddModuleExport(ctx, m, "FLAG_WINDOW_MOUSE_PASSTHROUGH");
    JS_AddModuleExport(ctx, m, "FLAG_BORDERLESS_WINDOWED_MODE");
    JS_AddModuleExport(ctx, m, "FLAG_MSAA_4X_HINT");
    JS_AddModuleExport(ctx, m, "FLAG_INTERLACED_HINT");
    JS_AddModuleExport(ctx, m, "LOG_ALL");
    JS_AddModuleExport(ctx, m, "LOG_TRACE");
    JS_AddModuleExport(ctx, m, "LOG_DEBUG");
    JS_AddModuleExport(ctx, m, "LOG_INFO");
    JS_AddModuleExport(ctx, m, "LOG_WARNING");
    JS_AddModuleExport(ctx, m, "LOG_ERROR");
    JS_AddModuleExport(ctx, m, "LOG_FATAL");
    JS_AddModuleExport(ctx, m, "LOG_NONE");
    JS_AddModuleExport(ctx, m, "KEY_NULL");
    JS_AddModuleExport(ctx, m, "KEY_APOSTROPHE");
    JS_AddModuleExport(ctx, m, "KEY_COMMA");
    JS_AddModuleExport(ctx, m, "KEY_MINUS");
    JS_AddModuleExport(ctx, m, "KEY_PERIOD");
    JS_AddModuleExport(ctx, m, "KEY_SLASH");
    JS_AddModuleExport(ctx, m, "KEY_ZERO");
    JS_AddModuleExport(ctx, m, "KEY_ONE");
    JS_AddModuleExport(ctx, m, "KEY_TWO");
    JS_AddModuleExport(ctx, m, "KEY_THREE");
    JS_AddModuleExport(ctx, m, "KEY_FOUR");
    JS_AddModuleExport(ctx, m, "KEY_FIVE");
    JS_AddModuleExport(ctx, m, "KEY_SIX");
    JS_AddModuleExport(ctx, m, "KEY_SEVEN");
    JS_AddModuleExport(ctx, m, "KEY_EIGHT");
    JS_AddModuleExport(ctx, m, "KEY_NINE");
    JS_AddModuleExport(ctx, m, "KEY_SEMICOLON");
    JS_AddModuleExport(ctx, m, "KEY_EQUAL");
    JS_AddModuleExport(ctx, m, "KEY_A");
    JS_AddModuleExport(ctx, m, "KEY_B");
    JS_AddModuleExport(ctx, m, "KEY_C");
    JS_AddModuleExport(ctx, m, "KEY_D");
    JS_AddModuleExport(ctx, m, "KEY_E");
    JS_AddModuleExport(ctx, m, "KEY_F");
    JS_AddModuleExport(ctx, m, "KEY_G");
    JS_AddModuleExport(ctx, m, "KEY_H");
    JS_AddModuleExport(ctx, m, "KEY_I");
    JS_AddModuleExport(ctx, m, "KEY_J");
    JS_AddModuleExport(ctx, m, "KEY_K");
    JS_AddModuleExport(ctx, m, "KEY_L");
    JS_AddModuleExport(ctx, m, "KEY_M");
    JS_AddModuleExport(ctx, m, "KEY_N");
    JS_AddModuleExport(ctx, m, "KEY_O");
    JS_AddModuleExport(ctx, m, "KEY_P");
    JS_AddModuleExport(ctx, m, "KEY_Q");
    JS_AddModuleExport(ctx, m, "KEY_R");
    JS_AddModuleExport(ctx, m, "KEY_S");
    JS_AddModuleExport(ctx, m, "KEY_T");
    JS_AddModuleExport(ctx, m, "KEY_U");
    JS_AddModuleExport(ctx, m, "KEY_V");
    JS_AddModuleExport(ctx, m, "KEY_W");
    JS_AddModuleExport(ctx, m, "KEY_X");
    JS_AddModuleExport(ctx, m, "KEY_Y");
    JS_AddModuleExport(ctx, m, "KEY_Z");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_BRACKET");
    JS_AddModuleExport(ctx, m, "KEY_BACKSLASH");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_BRACKET");
    JS_AddModuleExport(ctx, m, "KEY_GRAVE");
    JS_AddModuleExport(ctx, m, "KEY_SPACE");
    JS_AddModuleExport(ctx, m, "KEY_ESCAPE");
    JS_AddModuleExport(ctx, m, "KEY_ENTER");
    JS_AddModuleExport(ctx, m, "KEY_TAB");
    JS_AddModuleExport(ctx, m, "KEY_BACKSPACE");
    JS_AddModuleExport(ctx, m, "KEY_INSERT");
    JS_AddModuleExport(ctx, m, "KEY_DELETE");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT");
    JS_AddModuleExport(ctx, m, "KEY_LEFT");
    JS_AddModuleExport(ctx, m, "KEY_DOWN");
    JS_AddModuleExport(ctx, m, "KEY_UP");
    JS_AddModuleExport(ctx, m, "KEY_PAGE_UP");
    JS_AddModuleExport(ctx, m, "KEY_PAGE_DOWN");
    JS_AddModuleExport(ctx, m, "KEY_HOME");
    JS_AddModuleExport(ctx, m, "KEY_END");
    JS_AddModuleExport(ctx, m, "KEY_CAPS_LOCK");
    JS_AddModuleExport(ctx, m, "KEY_SCROLL_LOCK");
    JS_AddModuleExport(ctx, m, "KEY_NUM_LOCK");
    JS_AddModuleExport(ctx, m, "KEY_PRINT_SCREEN");
    JS_AddModuleExport(ctx, m, "KEY_PAUSE");
    JS_AddModuleExport(ctx, m, "KEY_F1");
    JS_AddModuleExport(ctx, m, "KEY_F2");
    JS_AddModuleExport(ctx, m, "KEY_F3");
    JS_AddModuleExport(ctx, m, "KEY_F4");
    JS_AddModuleExport(ctx, m, "KEY_F5");
    JS_AddModuleExport(ctx, m, "KEY_F6");
    JS_AddModuleExport(ctx, m, "KEY_F7");
    JS_AddModuleExport(ctx, m, "KEY_F8");
    JS_AddModuleExport(ctx, m, "KEY_F9");
    JS_AddModuleExport(ctx, m, "KEY_F10");
    JS_AddModuleExport(ctx, m, "KEY_F11");
    JS_AddModuleExport(ctx, m, "KEY_F12");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_SHIFT");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_CONTROL");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_ALT");
    JS_AddModuleExport(ctx, m, "KEY_LEFT_SUPER");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_SHIFT");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_CONTROL");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_ALT");
    JS_AddModuleExport(ctx, m, "KEY_RIGHT_SUPER");
    JS_AddModuleExport(ctx, m, "KEY_KB_MENU");
    JS_AddModuleExport(ctx, m, "KEY_KP_0");
    JS_AddModuleExport(ctx, m, "KEY_KP_1");
    JS_AddModuleExport(ctx, m, "KEY_KP_2");
    JS_AddModuleExport(ctx, m, "KEY_KP_3");
    JS_AddModuleExport(ctx, m, "KEY_KP_4");
    JS_AddModuleExport(ctx, m, "KEY_KP_5");
    JS_AddModuleExport(ctx, m, "KEY_KP_6");
    JS_AddModuleExport(ctx, m, "KEY_KP_7");
    JS_AddModuleExport(ctx, m, "KEY_KP_8");
    JS_AddModuleExport(ctx, m, "KEY_KP_9");
    JS_AddModuleExport(ctx, m, "KEY_KP_DECIMAL");
    JS_AddModuleExport(ctx, m, "KEY_KP_DIVIDE");
    JS_AddModuleExport(ctx, m, "KEY_KP_MULTIPLY");
    JS_AddModuleExport(ctx, m, "KEY_KP_SUBTRACT");
    JS_AddModuleExport(ctx, m, "KEY_KP_ADD");
    JS_AddModuleExport(ctx, m, "KEY_KP_ENTER");
    JS_AddModuleExport(ctx, m, "KEY_KP_EQUAL");
    JS_AddModuleExport(ctx, m, "KEY_BACK");
    JS_AddModuleExport(ctx, m, "KEY_MENU");
    JS_AddModuleExport(ctx, m, "KEY_VOLUME_UP");
    JS_AddModuleExport(ctx, m, "KEY_VOLUME_DOWN");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_LEFT");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_RIGHT");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_MIDDLE");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_SIDE");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_EXTRA");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_FORWARD");
    JS_AddModuleExport(ctx, m, "MOUSE_BUTTON_BACK");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_DEFAULT");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_ARROW");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_IBEAM");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_CROSSHAIR");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_POINTING_HAND");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_EW");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NS");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NWSE");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_NESW");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_RESIZE_ALL");
    JS_AddModuleExport(ctx, m, "MOUSE_CURSOR_NOT_ALLOWED");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_UNKNOWN");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_UP");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_RIGHT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_DOWN");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_FACE_LEFT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_UP");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_DOWN");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_FACE_LEFT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_1");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_TRIGGER_2");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_1");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_TRIGGER_2");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_LEFT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_MIDDLE_RIGHT");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_LEFT_THUMB");
    JS_AddModuleExport(ctx, m, "GAMEPAD_BUTTON_RIGHT_THUMB");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_X");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_Y");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_X");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_Y");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_LEFT_TRIGGER");
    JS_AddModuleExport(ctx, m, "GAMEPAD_AXIS_RIGHT_TRIGGER");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_ALBEDO");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_METALNESS");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_NORMAL");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_ROUGHNESS");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_OCCLUSION");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_EMISSION");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_HEIGHT");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_CUBEMAP");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_IRRADIANCE");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_PREFILTER");
    JS_AddModuleExport(ctx, m, "MATERIAL_MAP_BRDF");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_POSITION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD01");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_TEXCOORD02");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_NORMAL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_TANGENT");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VERTEX_COLOR");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_MVP");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_VIEW");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_PROJECTION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_MODEL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MATRIX_NORMAL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_VECTOR_VIEW");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_COLOR_DIFFUSE");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_COLOR_SPECULAR");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_COLOR_AMBIENT");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_ALBEDO");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_METALNESS");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_NORMAL");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_ROUGHNESS");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_OCCLUSION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_EMISSION");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_HEIGHT");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_CUBEMAP");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_IRRADIANCE");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_PREFILTER");
    JS_AddModuleExport(ctx, m, "SHADER_LOC_MAP_BRDF");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_FLOAT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_VEC4");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_INT");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC2");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC3");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_IVEC4");
    JS_AddModuleExport(ctx, m, "SHADER_UNIFORM_SAMPLER2D");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_FLOAT");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_VEC2");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_VEC3");
    JS_AddModuleExport(ctx, m, "SHADER_ATTRIB_VEC4");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G6B5");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_UNCOMPRESSED_R16G16B16A16");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT1_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT3_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_DXT5_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC1_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGB");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_PVRT_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA");
    JS_AddModuleExport(ctx, m, "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_POINT");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_BILINEAR");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_TRILINEAR");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_4X");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_8X");
    JS_AddModuleExport(ctx, m, "TEXTURE_FILTER_ANISOTROPIC_16X");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_REPEAT");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_CLAMP");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_REPEAT");
    JS_AddModuleExport(ctx, m, "TEXTURE_WRAP_MIRROR_CLAMP");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_AUTO_DETECT");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_VERTICAL");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_LINE_HORIZONTAL");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE");
    JS_AddModuleExport(ctx, m, "CUBEMAP_LAYOUT_PANORAMA");
    JS_AddModuleExport(ctx, m, "FONT_DEFAULT");
    JS_AddModuleExport(ctx, m, "FONT_BITMAP");
    JS_AddModuleExport(ctx, m, "FONT_SDF");
    JS_AddModuleExport(ctx, m, "BLEND_ALPHA");
    JS_AddModuleExport(ctx, m, "BLEND_ADDITIVE");
    JS_AddModuleExport(ctx, m, "BLEND_MULTIPLIED");
    JS_AddModuleExport(ctx, m, "BLEND_ADD_COLORS");
    JS_AddModuleExport(ctx, m, "BLEND_SUBTRACT_COLORS");
    JS_AddModuleExport(ctx, m, "BLEND_ALPHA_PREMULTIPLY");
    JS_AddModuleExport(ctx, m, "BLEND_CUSTOM");
    JS_AddModuleExport(ctx, m, "BLEND_CUSTOM_SEPARATE");
    JS_AddModuleExport(ctx, m, "GESTURE_NONE");
    JS_AddModuleExport(ctx, m, "GESTURE_TAP");
    JS_AddModuleExport(ctx, m, "GESTURE_DOUBLETAP");
    JS_AddModuleExport(ctx, m, "GESTURE_HOLD");
    JS_AddModuleExport(ctx, m, "GESTURE_DRAG");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_RIGHT");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_LEFT");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_UP");
    JS_AddModuleExport(ctx, m, "GESTURE_SWIPE_DOWN");
    JS_AddModuleExport(ctx, m, "GESTURE_PINCH_IN");
    JS_AddModuleExport(ctx, m, "GESTURE_PINCH_OUT");
    JS_AddModuleExport(ctx, m, "CAMERA_CUSTOM");
    JS_AddModuleExport(ctx, m, "CAMERA_FREE");
    JS_AddModuleExport(ctx, m, "CAMERA_ORBITAL");
    JS_AddModuleExport(ctx, m, "CAMERA_FIRST_PERSON");
    JS_AddModuleExport(ctx, m, "CAMERA_THIRD_PERSON");
    JS_AddModuleExport(ctx, m, "CAMERA_PERSPECTIVE");
    JS_AddModuleExport(ctx, m, "CAMERA_ORTHOGRAPHIC");
    JS_AddModuleExport(ctx, m, "NPATCH_NINE_PATCH");
    JS_AddModuleExport(ctx, m, "NPATCH_THREE_PATCH_VERTICAL");
    JS_AddModuleExport(ctx, m, "NPATCH_THREE_PATCH_HORIZONTAL");
    JS_AddModuleExport(ctx, m, "LIGHTGRAY");
    JS_AddModuleExport(ctx, m, "GRAY");
    JS_AddModuleExport(ctx, m, "DARKGRAY");
    JS_AddModuleExport(ctx, m, "YELLOW");
    JS_AddModuleExport(ctx, m, "GOLD");
    JS_AddModuleExport(ctx, m, "ORANGE");
    JS_AddModuleExport(ctx, m, "PINK");
    JS_AddModuleExport(ctx, m, "RED");
    JS_AddModuleExport(ctx, m, "MAROON");
    JS_AddModuleExport(ctx, m, "GREEN");
    JS_AddModuleExport(ctx, m, "LIME");
    JS_AddModuleExport(ctx, m, "DARKGREEN");
    JS_AddModuleExport(ctx, m, "SKYBLUE");
    JS_AddModuleExport(ctx, m, "BLUE");
    JS_AddModuleExport(ctx, m, "DARKBLUE");
    JS_AddModuleExport(ctx, m, "PURPLE");
    JS_AddModuleExport(ctx, m, "VIOLET");
    JS_AddModuleExport(ctx, m, "DARKPURPLE");
    JS_AddModuleExport(ctx, m, "BEIGE");
    JS_AddModuleExport(ctx, m, "BROWN");
    JS_AddModuleExport(ctx, m, "DARKBROWN");
    JS_AddModuleExport(ctx, m, "WHITE");
    JS_AddModuleExport(ctx, m, "BLACK");
    JS_AddModuleExport(ctx, m, "BLANK");
    JS_AddModuleExport(ctx, m, "MAGENTA");
    JS_AddModuleExport(ctx, m, "RAYWHITE");
    JS_AddModuleExport(ctx, m, "CAMERA_PERSPECTIVE");
    JS_AddModuleExport(ctx, m, "CAMERA_ORTHOGRAPHIC");
    JS_AddModuleExport(ctx, m, "CAMERA_CUSTOM");
    JS_AddModuleExport(ctx, m, "CAMERA_FREE");
    JS_AddModuleExport(ctx, m, "CAMERA_ORBITAL");
    JS_AddModuleExport(ctx, m, "CAMERA_FIRST_PERSON");
    JS_AddModuleExport(ctx, m, "CAMERA_THIRD_PERSON");
    JS_AddModuleExport(ctx, m, "GuiStyleProp");
    JS_AddModuleExport(ctx, m, "STATE_NORMAL");
    JS_AddModuleExport(ctx, m, "STATE_FOCUSED");
    JS_AddModuleExport(ctx, m, "STATE_PRESSED");
    JS_AddModuleExport(ctx, m, "STATE_DISABLED");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_LEFT");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_CENTER");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_RIGHT");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_TOP");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_MIDDLE");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGN_BOTTOM");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_NONE");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_CHAR");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_WORD");
    JS_AddModuleExport(ctx, m, "DEFAULT");
    JS_AddModuleExport(ctx, m, "LABEL");
    JS_AddModuleExport(ctx, m, "BUTTON");
    JS_AddModuleExport(ctx, m, "TOGGLE");
    JS_AddModuleExport(ctx, m, "SLIDER");
    JS_AddModuleExport(ctx, m, "PROGRESSBAR");
    JS_AddModuleExport(ctx, m, "CHECKBOX");
    JS_AddModuleExport(ctx, m, "COMBOBOX");
    JS_AddModuleExport(ctx, m, "DROPDOWNBOX");
    JS_AddModuleExport(ctx, m, "TEXTBOX");
    JS_AddModuleExport(ctx, m, "VALUEBOX");
    JS_AddModuleExport(ctx, m, "SPINNER");
    JS_AddModuleExport(ctx, m, "LISTVIEW");
    JS_AddModuleExport(ctx, m, "COLORPICKER");
    JS_AddModuleExport(ctx, m, "SCROLLBAR");
    JS_AddModuleExport(ctx, m, "STATUSBAR");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_NORMAL");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_NORMAL");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_NORMAL");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_FOCUSED");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_FOCUSED");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_FOCUSED");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_PRESSED");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_PRESSED");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_PRESSED");
    JS_AddModuleExport(ctx, m, "BORDER_COLOR_DISABLED");
    JS_AddModuleExport(ctx, m, "BASE_COLOR_DISABLED");
    JS_AddModuleExport(ctx, m, "TEXT_COLOR_DISABLED");
    JS_AddModuleExport(ctx, m, "BORDER_WIDTH");
    JS_AddModuleExport(ctx, m, "TEXT_PADDING");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGNMENT");
    JS_AddModuleExport(ctx, m, "TEXT_SIZE");
    JS_AddModuleExport(ctx, m, "TEXT_SPACING");
    JS_AddModuleExport(ctx, m, "LINE_COLOR");
    JS_AddModuleExport(ctx, m, "BACKGROUND_COLOR");
    JS_AddModuleExport(ctx, m, "TEXT_LINE_SPACING");
    JS_AddModuleExport(ctx, m, "TEXT_ALIGNMENT_VERTICAL");
    JS_AddModuleExport(ctx, m, "TEXT_WRAP_MODE");
    JS_AddModuleExport(ctx, m, "GROUP_PADDING");
    JS_AddModuleExport(ctx, m, "SLIDER_WIDTH");
    JS_AddModuleExport(ctx, m, "SLIDER_PADDING");
    JS_AddModuleExport(ctx, m, "PROGRESS_PADDING");
    JS_AddModuleExport(ctx, m, "ARROWS_SIZE");
    JS_AddModuleExport(ctx, m, "ARROWS_VISIBLE");
    JS_AddModuleExport(ctx, m, "SCROLL_SLIDER_PADDING");
    JS_AddModuleExport(ctx, m, "SCROLL_SLIDER_SIZE");
    JS_AddModuleExport(ctx, m, "SCROLL_PADDING");
    JS_AddModuleExport(ctx, m, "SCROLL_SPEED");
    JS_AddModuleExport(ctx, m, "CHECK_PADDING");
    JS_AddModuleExport(ctx, m, "COMBO_BUTTON_WIDTH");
    JS_AddModuleExport(ctx, m, "COMBO_BUTTON_SPACING");
    JS_AddModuleExport(ctx, m, "ARROW_PADDING");
    JS_AddModuleExport(ctx, m, "DROPDOWN_ITEMS_SPACING");
    JS_AddModuleExport(ctx, m, "DROPDOWN_ARROW_HIDDEN");
    JS_AddModuleExport(ctx, m, "DROPDOWN_ROLL_UP");
    JS_AddModuleExport(ctx, m, "TEXT_READONLY");
    JS_AddModuleExport(ctx, m, "SPIN_BUTTON_WIDTH");
    JS_AddModuleExport(ctx, m, "SPIN_BUTTON_SPACING");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_HEIGHT");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_SPACING");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_WIDTH");
    JS_AddModuleExport(ctx, m, "SCROLLBAR_SIDE");
    JS_AddModuleExport(ctx, m, "LIST_ITEMS_BORDER_WIDTH");
    JS_AddModuleExport(ctx, m, "COLOR_SELECTOR_SIZE");
    JS_AddModuleExport(ctx, m, "HUEBAR_WIDTH");
    JS_AddModuleExport(ctx, m, "HUEBAR_PADDING");
    JS_AddModuleExport(ctx, m, "HUEBAR_SELECTOR_HEIGHT");
    JS_AddModuleExport(ctx, m, "HUEBAR_SELECTOR_OVERFLOW");


    return m;
}