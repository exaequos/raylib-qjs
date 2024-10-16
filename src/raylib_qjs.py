import json
import sys
import re

#funcAuthorized = ['InitWindow', 'CloseWindow', 'WindowShouldClose', 'SetTargetFPS', 'BeginDrawing', 'EndDrawing', 'IsWindowReady', 'IsWindowFullscreen', 'IsWindowHidden', 'IsWindowMinimized', 'IsWindowMaximized', 'IsWindowFocused', 'IsWindowResized', 'IsWindowState', 'SetWindowState', 'ClearWindowState', 'ToggleFullscreen', 'ToggleBorderlessWindowed', 'MaximizeWindow', 'MinimizeWindow', 'RestoreWindow', 'LoadImage', 'SetWindowIcon', 'SetWindowTitle', 'SetWindowPosition', 'SetWindowMonitor', 'SetWindowMinSize', 'SetWindowMaxSize', 'SetWindowSize', 'SetWindowOpacity', 'SetWindowOpacity', 'SetWindowFocused', 'GetWindowHandle', 'GetScreenWidth', 'GetScreenHeight', 'GetRenderWidth', 'GetRenderHeight', 'GetMonitorCount', 'GetCurrentMonitor', 'GetMonitorPosition', 'GetMonitorWidth', 'GetMonitorHeight', 'GetMonitorPhysicalWidth', 'GetMonitorPhysicalHeight', 'GetMonitorRefreshRate', 'GetWindowPosition', 'GetWindowScaleDPI', 'GetMonitorName' ]
#structAuthorized = ['Vector2', 'Image']

funcNotExported = ['UnloadFileData', 'UnloadFileData', 'SetWindowIcons', 'TraceLog', 'SetTraceLogCallback', 'SetLoadFileDataCallback', 'SetSaveFileDataCallback', 'SetLoadFileTextCallback', 'SetSaveFileTextCallback', 'DrawLineStrip', 'DrawTriangleFan', 'DrawTriangleStrip', 'DrawSplineLinear', 'DrawSplineBasis', 'DrawSplineCatmullRom', 'DrawSplineBezierQuadratic', 'DrawSplineBezierCubic', 'LoadImageColors', 'LoadImagePalette', 'UnloadImageColors', 'UnloadImagePalette', 'LoadFontData', 'GenImageFontAtlas', 'UnloadFontData', 'TextFormat', 'GenTextureMipmaps', 'TextJoin', 'TextSplit', 'DrawTriangleStrip3D', 'UploadMesh', 'GenMeshTangents', 'LoadMaterials', 'SetMaterialTexture', 'DrawMeshInstanced', 'CheckCollisionPointPoly', 'CheckCollisionLines', 'SetModelMeshMaterial', 'LoadModelAnimations', 'UnloadModelAnimations', 'WaveCrop', 'WaveFormat', 'SetAudioStreamCallback', 'AttachAudioStreamProcessor', 'DetachAudioStreamProcessor', 'AttachAudioMixedProcessor', 'DetachAudioMixedProcessor', 'UnloadWaveSamples' ]

RayType = {
    'double': { 'q': 'Float64', 'r': 'double'},
    'float': { 'q': 'Float64', 'r': 'double'},
    'void *': { 'q': 'Uint32', 'r': 'unsigned int'},
    'const void *': { 'q': 'Uint32', 'r': 'unsigned int'},
    'int': { 'q': 'Int32', 'r': 'int'},
    'unsigned char': { 'q': 'Uint32', 'r': 'unsigned int'},
    'unsigned int': { 'q': 'Uint32', 'r': 'unsigned int'},
    'bool': { 'q': 'Int32', 'r': 'JS_BOOL'},
    'unsigned short': { 'q': 'Uint32', 'r': 'unsigned short'},
}

customCalls = {

    'LoadFileData': {

        'call': '''const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);
    size_t data_size1;
    int * arg1 = (int *)JS_GetArrayBuffer(ctx, &data_size1, argv[1]);

    unsigned char * retVal = LoadFileData(arg0, &data_size1);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, data_size1);

    UnloadFileData(retVal);
    return ret;''',
        'nb_args': 2
    },
    'LoadFileText': {

        'call': '''const char * arg0 = (const char *)JS_ToCString(ctx, argv[0]);

    char * retVal = LoadFileText(arg0);

    JS_FreeCString(ctx, arg0);

    JSValue ret = JS_NewString(ctx, retVal);

    UnloadFileText(retVal);
    return ret;''',
        'nb_args': 1
    },
    'GuiTabBar': {

        'call': '''

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

    return JS_NewInt32(ctx, ret);''',
        'nb_args': 4
    },
    'UnloadFileData': {

        'call': '''return JS_UNDEFINED;''',
        'nb_args': 0
    },
    'UnloadFileText': {

        'call': '''return JS_UNDEFINED;''',
        'nb_args': 0
    },
}

funcList = ''
symbolList = ''
enumDeclare = ''
structDeclare = ''
defineDeclare = ''

customTypes = []
customTypesPtr = {}

callbacks = {}
aliases = {}

def parseStruct(struct, type = None):

    global customTypes
    global symbolList
    global structDeclare

    if struct['name'] in customTypes:
        return
    
    #print("Parsing structure ", struct['name'])

    #if struct['name'] not in structAuthorized:
    #    return

    symbolList += '    JS_AddModuleExport(ctx, m, "{0}");\n'.format(struct['name'])

    structDeclare += '    js_declare_{0}(ctx, m);\n'.format(struct['name'])

    propList = ''
    propSet = ''
    propGet = ''
    propCtor = ''

    i = 0

    if type is None:
        fields = struct['fields']
    else:
        fields = type['fields']

    for p in fields:
        propList += '    JS_CGETSET_MAGIC_DEF("{0}", js_{1}_get, js_{1}_set, {2}),\n'.format(p['name'], struct['name'], i)

        #        arguments += '''    {0} * argptr{1} = ({0} *)JS_GetOpaque2(ctx, argv[0], js_{0}_class_id);
        
        if p['type']  == 'Rectangle *' or  p['type']  == 'GlyphInfo *' or  p['type']  == 'MaterialMap *' or  p['type']  == 'Material *' or  p['type']  == 'Mesh *' or  p['type']  == 'BoneInfo *' or  p['type']  == 'Transform *' or  p['type']  == 'Transform **' or  p['type']  == 'AutomationEvent *':
        
            propGet += '''
            '''
            propSet += '''
            '''
            propCtor += '''
            '''
        elif p['type'] in customTypes:
        
            propGet += '''
if (magic == {1}) {{
    {0}* ret_ptr = ({0} *)js_malloc(ctx, sizeof({0}));
    *ret_ptr = s->{2};
    JSValue ret = JS_NewObjectClass(ctx, js_{0}_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
}}
'''.format(p['type'], i, p['name'])
            propSet += '''
if (magic == {1}) {{
    {0} * argptr{1} = ({0} *)JS_GetOpaque2(ctx, val, js_{0}_class_id);
    
    if (argptr{1} == NULL) return JS_EXCEPTION;
                    
    s->{2} = *argptr{1};
}}
'''.format(p['type'], i, p['name'])
            propCtor += '''
    {0} * argptr{1} = ({0} *)JS_GetOpaque2(ctx, argv[{1}], js_{0}_class_id);
                    
    if (argptr{1} == NULL) return JS_EXCEPTION;
                    
    s->{2} = *argptr{1};
'''.format(p['type'], i, p['name'])
        elif p['type'] in RayType:
            propGet += '''
if (magic == {0}) {{
    return JS_New{1}(ctx, ({3}) s->{2});
}}
'''.format(i, RayType[p['type']]['q'], p['name'], RayType[p['type']]['r'])

            propSet += '''
if (magic == {0}) {{
    {1} v{0};
    if (JS_To{2}(ctx, &v{0}, val))
        return JS_EXCEPTION;
    s->{3} = ({4}) v{0};
}}
'''.format(i, RayType[p['type']]['r'], RayType[p['type']]['q'], p['name'], p['type'])

            propCtor += '''
{1} v{0};
if (JS_To{2}(ctx, &v{0}, argv[{0}]))
        goto fail;
s->{3} = ({4}) v{0};

/*emscripten_log(EM_LOG_CONSOLE, "Set prop: {0} = %lf", s->{0});*/
        
'''.format(i, RayType[p['type']]['r'], RayType[p['type']]['q'], p['name'], p['type'])
        
        elif p['type'][-1] == '*' or p['type'][-1] == ']':
            '''size_t data_size;
            void * data_js = (void *)JS_GetArrayBuffer(ctx, &data_size, argv[1]);'''
            
            propGet += '''
            '''
            propSet += '''
            '''
            propCtor += '''
            '''
        
        i += 1

    sys.stdout.write('''

static JSClassID js_{0}_class_id;

static JSValue js_{0}_get(JSContext *ctx, JSValueConst this_val, int magic)
{{
    {0} *s = JS_GetOpaque2(ctx, this_val, js_{0}_class_id);
    if (!s)
        return JS_EXCEPTION;

    {2}

    return JS_UNDEFINED;
}}

static JSValue js_{0}_set(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{{
    {0} *s = JS_GetOpaque2(ctx, this_val, js_{0}_class_id);
    if (!s)
        return JS_EXCEPTION;

    {3}
    
    return JS_UNDEFINED;
}}

static void js_{0}_finalizer(JSRuntime *rt, JSValue val)
{{
    {0} *s = JS_GetOpaque(val, js_{0}_class_id);
    /* Note: 's' can be NULL in case JS_SetOpaque() was not called */
    js_free_rt(rt, s);
}}

static JSValue js_{0}_ctor(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{{

    /*emscripten_log(EM_LOG_CONSOLE, "--> js_{0}_ctor: argc=%d", argc);

    for (int i=0; i < argc; ++i) {{

      emscripten_log(EM_LOG_CONSOLE, "%d: %d", i, JS_VALUE_GET_TAG(argv[i]));
    }}*/
    
    {0} *s;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    s = js_mallocz(ctx, sizeof(*s));
    if (!s)
        return JS_EXCEPTION;
    
    /* using new_target to get the prototype is necessary when the
       class is extended. */
    {4}
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        goto fail;
    obj = JS_NewObjectProtoClass(ctx, proto, js_{0}_class_id);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, s);
    return obj;
 fail:
    js_free(ctx, s);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}}

static JSClassDef js_{0}_class = {{
    "{0}",
    .finalizer = js_{0}_finalizer,
}};

static const JSCFunctionListEntry js_{0}_proto_funcs[] = {{
{1}
    /*JS_PROP_STRING_DEF("[Symbol.toStringTag]", "{0}", JS_PROP_CONFIGURABLE ),*/
}};
    
static int js_declare_{0}(JSContext *ctx, JSModuleDef *m)
{{
    JSValue proto, class;

    /* create the class */
    JS_NewClassID(&js_{0}_class_id);
    JS_NewClass(JS_GetRuntime(ctx), js_{0}_class_id, &js_{0}_class);

    proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, js_{0}_proto_funcs, countof(js_{0}_proto_funcs));

    class = JS_NewCFunction2(ctx, js_{0}_ctor, "{0}", {5}, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, class, proto);
    JS_SetClassProto(ctx, js_{0}_class_id, proto);

    JS_SetModuleExport(ctx, m, "{0}", class);
    return 0;
}}

'''.format(struct['name'], propList, propGet, propSet, propCtor, i))
    
    customTypes.append(struct['name'])
    customTypesPtr[struct['name'] + " *"] = struct['name']
    customTypesPtr[struct['name'] + "*"] = struct['name']
    #customTypes.append(struct['name']+' *')
    #customTypes.append(struct['name']+' **')
    #customTypes.append('const '+struct['name']+' *')
    
#end of parseStruct

def parseFunc(func):

    #print("Parsing function ", func['name'])

    global funcNotExported

    if func['name'] in funcNotExported or func['name'][:5] == 'Image':
        return

    s = 'static JSValue js_{0}(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv)'.format(func['name'])

    global customTypes
    global funcList
    global customCalls
    global aliases

    if func['name'] in customCalls:
        if 'call' in customCalls[func['name']]:
            call = customCalls[func['name']]['call']
            funcList += '    JS_CFUNC_DEF("{0}", {1}, js_{0} ),\n'.format(func['name'], customCalls[func['name']]['nb_args'])
    else:
        arguments = ''
        parameters = ''
        freeCalls = ''

        i = 0
    
        if 'params' in func:
        
            for p in func['params']:

                a = ''
            
                if p['type'] == 'int':
                    arguments += '    int arg{0};\n    JS_ToInt32(ctx, &arg{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'unsigned int':
                    arguments += '    unsigned int arg{0};\n    JS_ToUint32(ctx, &arg{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'bool':
                    arguments += '    JS_BOOL argbool{0} = JS_ToBool(ctx, argv[{0}]);\n    bool arg{0} = (bool) argbool{0};\n'.format(i)
                elif p['type'] == 'float':
                    arguments += '    double arg{0};\n    JS_ToFloat64(ctx, &arg{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'double':
                    arguments += '    double arg{0};\n    JS_ToFloat64(ctx, &arg{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'char':
                    pass
                elif p['type'] == 'char *':
                    arguments += '''    JSValue arg{0}_js = JS_GetPropertyStr(ctx, argv[{0}], "{1}");
    size_t arg{0}_len;
    const char * arg{0}_str = JS_ToCStringLen(ctx, &arg{0}_len, arg{0}_js);
    char * arg{0} = malloc(arg{0}_len+1);
    memcpy((void *)arg{0}, arg{0}_str, arg{0}_len);
    arg{0}[arg{0}_len] = 0;
                '''.format(i, p['name'])
                    freeCalls += '''    JS_FreeCString(ctx, arg{0}_str);
                JS_SetPropertyStr(ctx, argv[{0}], "{1}", JS_NewString(ctx, arg{0}));
                free(arg{0});\n'''.format(i, p['name'])
                elif p['type'] == 'const char *':
                    #arguments += 'const char * arg{0} = ((struct JSString *)JS_VALUE_GET_PTR(argv[0]))->u.str8;'.format(i)
                    arguments += '    const char * arg{0} = (const char *)JS_ToCString(ctx, argv[{0}]);\n'.format(i)
                    freeCalls += '    JS_FreeCString(ctx, arg{0});\n'.format(i)
                elif p['type'] == 'const char **':
                    arguments += 'size_t data_size{0};\n    const char ** arg{0} = (const char **)JS_GetArrayBuffer(ctx, &data_size{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'unsigned char *':
                    arguments += 'size_t data_size{0};\n    unsigned char * arg{0} = (unsigned char *)JS_GetArrayBuffer(ctx, &data_size{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'const unsigned char *':
                    arguments += 'size_t data_size{0};\n    const unsigned char * arg{0} = (const unsigned char *)JS_GetArrayBuffer(ctx, &data_size{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'const void *':
                    arguments += 'size_t data_size{0};\n    const void * arg{0} = (const void *)JS_GetArrayBuffer(ctx, &data_size{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'void *':
                    arguments += 'size_t data_size{0};\n    void * arg{0} = (void *)JS_GetArrayBuffer(ctx, &data_size{0}, argv[{0}]);\n'.format(i)
                elif p['type'] == 'int *':
                    arguments += '''JSValue arg{0}_js = JS_GetPropertyStr(ctx, argv[{0}], "{1}");
    int arg{0}_int;
    JS_ToInt32(ctx, &arg{0}_int, arg{0}_js);
    int * arg{0} = &arg{0}_int;
                    '''.format(i, p['name'])
                    freeCalls += 'JS_SetPropertyStr(ctx, argv[{0}], "{1}", JS_NewInt32(ctx, arg{0}_int));\n'.format(i, p['name'])
                elif p['type'] == 'const int *':
                    arguments += '''JSValue arg{0}_js = JS_GetPropertyStr(ctx, argv[{0}], "{1}");
    int arg{0}_int;
    JS_ToInt32(ctx, &arg{0}_int, arg{0}_js);
    int * arg{0} = &arg{0}_int;
                    '''.format(i, p['name'])
                    freeCalls += 'JS_SetPropertyStr(ctx, argv[{0}], "{1}", JS_NewInt32(ctx, arg{0}_int));\n'.format(i, p['name'])
                elif p['type'] == 'float *':
                    arguments += '''JSValue arg{0}_js = JS_GetPropertyStr(ctx, argv[{0}], "{1}");
    double arg{0}_double;
    JS_ToFloat64(ctx, &arg{0}_double, arg{0}_js);
    float  arg{0}_float = (float)arg{0}_double;
    float * arg{0} = &arg{0}_float;
                    '''.format(i, p['name'])
                    freeCalls += 'JS_SetPropertyStr(ctx, argv[{0}], "{1}", JS_NewFloat64(ctx, arg{0}_float));\n'.format(i, p['name'])
                elif p['type'] == 'bool *':
                    arguments += '''JSValue arg{0}_js = JS_GetPropertyStr(ctx, argv[{0}], "{1}");
    int arg{0}_int;
    JS_ToInt32(ctx, &arg{0}_int, arg{0}_js);
    int * arg{0} = &arg{0}_int;
                    '''.format(i, p['name'])
                    freeCalls += 'JS_SetPropertyStr(ctx, argv[{0}], "{1}", JS_NewInt32(ctx, arg{0}_int));\n'.format(i, p['name'])
                elif p['type'] == '...':
                    pass
                elif p['type'] in customTypes:
                    arguments += '''    {0} * argptr{1} = ({0} *)JS_GetOpaque2(ctx, argv[{1}], js_{0}_class_id);
'''.format(p['type'], i)

                    if p['type'] in aliases:
                        arguments += '''        if (argptr{1} == NULL)
        argptr{1} = ({0} *)JS_GetOpaque2(ctx, argv[{1}], js_{2}_class_id);
'''.format(p['type'], i, aliases[p['type']])
                    
                    arguments += '''        if (argptr{1} == NULL) return JS_EXCEPTION;
                    
        {0} arg{1} = *argptr{1};
'''.format(p['type'], i)
                elif p['type'] in customTypesPtr:
                    arguments += '''    {0} * arg{1} = ({0} *)JS_GetOpaque2(ctx, argv[{1}], js_{0}_class_id);
'''.format(customTypesPtr[p['type']], i)

                    if customTypesPtr[p['type']] in aliases:
                        arguments += '''        if (arg{1} == NULL)
        arg{1} = ({0} *)JS_GetOpaque2(ctx, argv[{1}], js_{2}_class_id);
'''.format(customTypesPtr[p['type']], i, aliases[customTypesPtr[p['type']]])
                    
                elif p['type'] in callbacks:
                    pass
                else:
                    sys.stderr.write('param type not supported: {0}\n'.format(p['type']))
                    exit(0)
                

                if i > 0:
                    parameters += ', '
                parameters += 'arg{0}'.format(i)
                i += 1
                
        funcList += '    JS_CFUNC_DEF("{0}", {1}, js_{0} ),\n'.format(func['name'], i)

        assign = ''
        ret = ''
        call = ''
    
        if func['returnType'] == 'void':
            assign = ''
            ret = 'return JS_UNDEFINED;'
        elif func['returnType'] == 'int':
            assign = 'int ret = '
            ret = 'return JS_NewInt32(ctx, ret);'
        elif func['returnType'] == 'bool':
            assign = 'bool ret = '
            ret = 'return JS_NewBool(ctx, ret);'
        elif func['returnType'] == 'unsigned int':
            assign = 'unsigned int ret = '
            ret = 'return JS_NewUint32(ctx, ret);'
        elif func['returnType'] == 'long':
            assign = 'long ret = '
            ret = 'return JS_NewInt64(ctx, ret);'
        elif func['returnType'] == 'float':
            assign = 'float ret = '
            ret = 'return JS_NewFloat64(ctx, ret);'
        elif func['returnType'] == 'double':
            assign = 'double ret = '
            ret = 'return JS_NewFloat64(ctx, ret);'
        elif func['returnType'] == 'void *':
            assign = 'void * ret = '
            ret = 'return JS_NewUint32(ctx, (unsigned int) ret);'
        elif func['returnType'] == 'int *':
            assign = 'int * retBuf = '
            ret = '''JSValue ret = JS_NewArray(ctx);
    for(int i; i < 7777 /*<<size>>*/; i++){
        JS_SetPropertyUint32(ctx, ret, i, JS_NewInt32(ctx, retBuf[i]));
    }
        return ret;
        '''
        elif func['returnType'] == 'char *':
            assign = 'char * retVal = '
            ret = 'JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);\n   return ret;'
        elif func['returnType'] == 'float *':
            assign = 'float * retBuf = '
            ret = '''JSValue ret = JS_NewArray(ctx);
            //TODO
            return ret;
        '''
        elif func['returnType'] == 'const char *':
            assign = '{0} returnVal = '.format(func['returnType'])
            ret = 'JSValue ret = JS_NewString(ctx, returnVal);\n    return ret;'
        elif func['returnType'] == 'const char **':
            pass
        elif func['returnType'] == 'unsigned char *':
            assign = 'unsigned char * retVal = ';
            ret = 'JSValue ret = JS_NewArrayBufferCopy(ctx, (const uint8_t*)retVal, 7777 /*<<size>>*/);\n    return ret;';
        elif func['returnType'] in customTypes:
            assign = '{0} returnVal = '.format(func['returnType'])
            ret = '''
    {0}* ret_ptr = ({0} *)js_malloc(ctx, sizeof({0}));
    *ret_ptr = returnVal;
    JSValue ret = JS_NewObjectClass(ctx, js_{0}_class_id);
    JS_SetOpaque(ret, ret_ptr);
    return ret;
    '''.format(func['returnType'])
        else:
            sys.stderr.write('return type not supported: {0}\n'.format(func['returnType']))
            exit(0)
            
    if len(call) > 0:
        s += "\n{{\n{0}\n}}\n\n".format(call)
    else:
        s += "\n{{\n{0}\n    {1}{2}({3});\n\n{4}\n    {5}\n}}\n\n".format(arguments, assign, func['name'], parameters, freeCalls, ret)

    sys.stdout.write(s)

#end of parseFunc

def parseCallback(callback):

    global callbacks

    if callback['name'] in callbacks:
        return

    signature = callback['returnType'] + ' (*' + callback['name'] + ')('

    i = 0
    for p in callback['params']:
        if i > 0:
            signature += ', '
        i += 1
        if p['type'] == 'va_list':
            signature += '...'
        else:
            signature += p['type']

    signature += ')'
        
    callbacks[callback['name']] = signature

def parseEnum(enum):

    global enumDeclare
    global symbolList

    if 'values' in enum:
        for v in enum['values']:

            enumDeclare += '    JS_SetModuleExport(ctx, m, "{0}", JS_NewInt32(ctx, {0}));\n'.format(v['name'], v['value'])
            symbolList += '    JS_AddModuleExport(ctx, m, "{0}");\n'.format(v['name'])

def parseDefine(define):

    global defineDeclare
    global symbolList

    #print(type(define['value']))

    if type(define['value']) == str and define['value'][0:8] == 'CLITERAL':
        m = re.search('CLITERAL[(](.*)[)][{](.*)[}]', define['value'])
        #print(m.group(0), m.group(1), m.group(2))

        if m.group(1) in customTypes:

            symbolList += '    JS_AddModuleExport(ctx, m, "{0}");\n'.format(define['name'])
            
            defineDeclare += '''    {0} {1}_struct = {{ {2} }}; 
{0}* {1}_js_ptr = ({0} *)js_malloc(ctx, sizeof({0}));
*{1}_js_ptr = {1}_struct;
JSValue {1}_js = JS_NewObjectClass(ctx, js_{0}_class_id);
JS_SetOpaque({1}_js, {1}_js_ptr);
JS_SetModuleExport(ctx, m, "{1}", {1}_js);
'''.format(m.group(1), define['name'], m.group(2))

def parseFile(file_name):

    with open(file_name, 'r') as file:
        data = json.load(file)

    #print(data.keys())
    
    for s in data['structs']:
        parseStruct(s)

        for alias in data['aliases']:
            if alias['type'] == s['name']:
                parseStruct(alias, s)
                aliases[alias['name']] = alias['type']
                aliases[alias['type']] = alias['name']

    for c in data['callbacks']:
        parseCallback(c)
        
    for f in data['functions']:
        parseFunc(f)

    for e in data['enums']:
        parseEnum(e)

    for d in data['defines']:
        parseDefine(d)

        
#end of parseFile

if __name__ == '__main__':
    sys.stdout.write('''#include "quickjs.h"
    
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

''')

    for arg in sys.argv[1:]:
        parseFile(arg)

    sys.stdout.write('static const JSCFunctionListEntry js_raylib_funcs[] = {\n'+funcList+'};\n')

    sys.stdout.write('static int js_raylib_init(JSContext *ctx, JSModuleDef *m)\n{{\n    JS_SetModuleExportList(ctx, m, js_raylib_funcs, countof(js_raylib_funcs));\n\n{0}\n{1}\n{2}\n    return 0;\n}}\n'.format(structDeclare, enumDeclare, defineDeclare))

    sys.stdout.write('''JSModuleDef *js_init_module(JSContext *ctx, const char *module_name)
{{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_raylib_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_raylib_funcs, countof(js_raylib_funcs));

{0}

    return m;
}}'''.format(symbolList))