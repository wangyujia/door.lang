



var test_parse = function(str) {
    var chr = {
        ' '  : "char_space",
        '\r' : "char_space",
        '\n' : "char_space",
        '\t' : "char_space",
        '\'' : "char_single_quot",
        '\"' : "char_double_quot",
        '('  : "char_left_pare",
        ')'  : "char_right_pare",
        '['  : "char_left_bracket",
        ']'  : "char_right_bracket",
        '{'  : "char_left_brace",
        '}'  : "char_right_brace",
        '='  : "char_equal",
        '+'  : "char_plus",
        '-'  : "char_dash",
        '*'  : "char_asterisk",
        '/'  : "char_slash",
        '\\' : "char_backslash",
        '~'  : "char_tilde",
        '!'  : "char_exclamation",
        '@'  : "char_at",
        '#'  : "char_hash",
        '$'  : "char_dollar",
        '%'  : "char_percent",
        '^'  : "char_caret",
        '&'  : "char_and",
        '|'  : "char_or",
        '_'  : "char_underscore",
        ','  : "char_comma",
        ';'  : "char_semicolon",
        '.'  : "char_dot",
        '0'  : "char_zero",
        '1'  : "char_num",
        '2'  : "char_num",
        '3'  : "char_num",
        '4'  : "char_num",
        '5'  : "char_num",
        '6'  : "char_num",
        '7'  : "char_num",
        '8'  : "char_num",
        '9'  : "char_num",
        'a'  : "char_lex",
        'b'  : "char_lex",
        'c'  : "char_lex",
        'd'  : "char_lex",
        'e'  : "char_lex",
        'f'  : "char_lex",
        'g'  : "char_lex",
        'h'  : "char_lex",
        'i'  : "char_lex",
        'j'  : "char_lex",
        'k'  : "char_lex",
        'l'  : "char_lex",
        'm'  : "char_lex",
        'n'  : "char_lex",
        'o'  : "char_lex",
        'p'  : "char_lex",
        'q'  : "char_lex",
        'r'  : "char_lex",
        's'  : "char_lex",
        't'  : "char_lex",
        'u'  : "char_lex",
        'v'  : "char_lex",
        'w'  : "char_lex",
        'x'  : "char_lex",
        'y'  : "char_lex",
        'z'  : "char_lex",
        'A'  : "char_lex",
        'B'  : "char_lex",
        'C'  : "char_lex",
        'D'  : "char_lex",
        'E'  : "char_lex",
        'F'  : "char_lex",
        'G'  : "char_lex",
        'H'  : "char_lex",
        'I'  : "char_lex",
        'J'  : "char_lex",
        'K'  : "char_lex",
        'L'  : "char_lex",
        'M'  : "char_lex",
        'N'  : "char_lex",
        'O'  : "char_lex",
        'P'  : "char_lex",
        'Q'  : "char_lex",
        'R'  : "char_lex",
        'S'  : "char_lex",
        'T'  : "char_lex",
        'U'  : "char_lex",
        'V'  : "char_lex",
        'W'  : "char_lex",
        'X'  : "char_lex",
        'Y'  : "char_lex",
        'Z'  : "char_lex",
    };
    var hex = {
        '0'  : "char_hex",
        '1'  : "char_hex",
        '2'  : "char_hex",
        '3'  : "char_hex",
        '4'  : "char_hex",
        '5'  : "char_hex",
        '6'  : "char_hex",
        '7'  : "char_hex",
        '8'  : "char_hex",
        '9'  : "char_hex",
        'a'  : "char_hex",
        'b'  : "char_hex",
        'c'  : "char_hex",
        'd'  : "char_hex",
        'e'  : "char_hex",
        'f'  : "char_hex",
        'A'  : "char_hex",
        'B'  : "char_hex",
        'C'  : "char_hex",
        'D'  : "char_hex",
        'E'  : "char_hex",
        'F'  : "char_hex",
    };
    var lex = {
        "var"       : "var_define",
        "fun"       : "fun_define",
        "if"        : "if_define",
        "for"       : "for_define",
        "while"     : "while_define",
        "switch"    : "switch_define",
        "case"      : "case_define",
        "continue"  : "continue_define",
        "break"     : "break_define",
    };
    var opt = {
        "::"        : {prio:0,  count:1, name:""},
        "[]"        : {prio:1,  count:2, name:""},
        "()"        : {prio:1,  count:2, name:""},
        "."         : {prio:1,  count:2, name:""},
        ":"         : {prio:1,  count:2, name:""},
        "prev++"    : {prio:2,  count:1, name:""},
        "prev--"    : {prio:2,  count:1, name:""},
        "next++"    : {prio:2,  count:1, name:""},
        "next--"    : {prio:2,  count:1, name:""},
        "!"         : {prio:2,  count:1, name:""},
        "~"         : {prio:2,  count:1, name:""},
        "positive+" : {prio:2,  count:1, name:""},
        "negative-" : {prio:2,  count:1, name:""},
        "typeof"    : {prio:2,  count:1, name:""},
        "sizeof"    : {prio:2,  count:1, name:""},
        "/"         : {prio:3,  count:2, name:"div", src:2},
        "%"         : {prio:3,  count:2, name:"mod", src:2},
        "*"         : {prio:3,  count:2, name:"mul", src:2},
        "+"         : {prio:4,  count:2, name:"add", src:2},
        "-"         : {prio:4,  count:2, name:"sub", src:2},
        "<<"        : {prio:5,  count:2, name:"left-shift",  src:2},
        ">>"        : {prio:5,  count:2, name:"right-shift", src:2},
        ">"         : {prio:6,  count:2, name:""},
        ">="        : {prio:6,  count:2, name:""},
        "<"         : {prio:6,  count:2, name:""},
        "<="        : {prio:6,  count:2, name:""},
        "=="        : {prio:7,  count:2, name:""},
        "!="        : {prio:7,  count:2, name:""},
        "&"         : {prio:8,  count:2, name:"bit-and", src:2},
        "^"         : {prio:9,  count:2, name:"bit-xor", src:2},
        "|"         : {prio:10, count:2, name:"bit-or",  src:2},
        "&&"        : {prio:11, count:2, name:"log-and", src:2},
        "||"        : {prio:12, count:2, name:"log-or",  src:2},
        "?:"        : {prio:13, count:3, name:""},
        ","         : {prio:14, count:2, name:""},
        "="         : {prio:15, count:2, name:"mov", dst:1, src:1},
        "/="        : {prio:15, count:2, name:"div", dst:1, src:2},
        "%="        : {prio:15, count:2, name:"mod", dst:1, src:2},
        "*="        : {prio:15, count:2, name:"mul", dst:1, src:2},
        "+="        : {prio:15, count:2, name:"add", dst:1, src:2},
        "-="        : {prio:15, count:2, name:"sub", dst:1, src:2},
        "<<="       : {prio:15, count:2, name:"left-shift",  dst:1, src:2},
        ">>="       : {prio:15, count:2, name:"right-shift", dst:1, src:2},
        "&="        : {prio:15, count:2, name:"bit-and", dst:1, src:2},
        "^="        : {prio:15, count:2, name:"bit-xor", dst:1, src:2},
        "|="        : {prio:15, count:2, name:"bit-or",  dst:1, src:2},
    };

    var object = {
        state: "init",
        index: 0,
        codes: []
    };
    
    /*
        /// 1 所有一切都是函数
        /// 2 只有在对函数进行点操作('.')时，才能把函数当成对象

        var t = fun {
            var b = fun(x) {
                x++;
            }

            /// typeof
            /// nameof
            /// operof
            /// fileof
            /// lineof
            /// callof

            fun(m, ...) {
                case(operof(m)) {
                    a: (6);
                    b: ((operof(m) == "call")? b(...) : b);
                }
            }
        }

        var f = t();
        f.a += 5;
        f.b(f.a);

        
        var x = fun {
            fun (...) {
                each(..., fun(m,o,v) {
                    
                });
            }
        }

        x(a=1, b=2);

        
    */

    /**
     * 寄存器就是相当于一个栈
     * 局部变量优先从底部分配
     * 函数参数优先从顶部分配
     */
    var regs = [];
    var reg_push = function(val) {
        regs[regs.length] = val;
        return regs.length - 1;
    };
    var reg_pop = function(count) {
        if (!count) count = 1;
        if (count > regs.length) count = regs.length;
        regs.length -= count;
    };
    var reg_tmp = [];
    var reg_tmp_new = function() {
        for (var i = 0; i < reg_tmp.length; ++i) {
            if (reg_tmp[i].ref == 0) {
                return reg_tmp[i].idx;
            }
        }
        var tmp_idx = reg_push();
        reg_tmp[reg_tmp.length] = {idx:tmp_idx,ref:0};
        return tmp_idx;
    };
    var reg_tmp_ref = function(reg, rel) {
        for (var i = 0; i < reg_tmp.length; ++i) {
            var tmp = "r" + reg_tmp[i].idx;
            if (tmp == reg) {
                if (rel) reg_tmp[i].ref++;
                else if (reg_tmp[i].ref > 0) reg_tmp[i].ref--;
                return;
            }
        }
    };
    var reg_tmp_pop = function() {
        var tmp_pop = function() {
            for (var i = 0; i < reg_tmp.length; ++i) {
                if ((reg_tmp[i].ref == 0) && 
                    (reg_tmp[i].idx == (regs.length - 1))) {
                    reg_pop();
                    reg_tmp.length--;
                    return true;
                }
            }
            return false;
        }
        while ((regs.length > 0) && (reg_tmp.length > 0)) {
            if (!tmp_pop()) break;
        }
    };

    var ins_out = function(name, args) {
        var ins_ptr = object.codes.length;
        object.codes[object.codes.length] = {
            name: name,
            args: args
        };
        return ins_ptr;
    };

    var ins_log = function(str) {
        object.codes[object.codes.length - 1].log.push(str);
    };

    var ins_exe = function(code) {
        var get = function(idx) {
            if (idx >= code.args.length) return;
            var node = code.args[idx];
            if (node[0] == 'r') {
                var reg_idx = parseInt(node.substring(1));
                return regs[reg_idx];
            }
            return node;
        };
        var set = function(idx, val) {
            if (idx >= code.args.length) return;
            var node = code.args[idx];
            if (node[0] == 'r') {
                var reg_idx = parseInt(node.substring(1));
                regs[reg_idx] = val;
            }
        };
        var exe = {
            mov: function() {
                set(0, get(1));
            },
            add: function() {
                set(0, get(1) + get(2));
            },
            sub: function() {
                set(0, get(1) - get(2));
            },
            mul: function() {
                set(0, get(1) * get(2));
            },
            div: function() {
                set(0, get(1) / get(2));
            },
            mod: function() {
                set(0, get(1) % get(2));
            },
            call: function() {

            },
        };
        exe[code.name]();
    }

    var vars = {};
    var states = [];
    var state_nref = 0;
    var state_curr = "lex_entry";
    var state_proc = function(type, token, state) {
        var state_push = function(op) {
            /// 操作对象和操作符必须一起到最后的栈顶
            states[states.length] = {
                state: state_curr,
                count: state_nref,
                index: object.index,
                value: token,
                opera: op
            };
            state_nref++;
            return states[states.length - 1];
        };
        var state_pop = function(count) {
            if (states.length <= 0) return;
            if (!count || (count <= 0)) count = 1;
            if (count > states.length) count = states.length;
            states.length -= count;
            if (state_nref < count) state_nref = 0;
            else state_nref -= count;
        };
        var state_top = function(index) {
            if (states.length <= 0) return;
            if (!index) index = 0;
            if (index >= 0) {
                if (index >= states.length) return;
                return states[states.length - 1 - index];
            }
            index = -1 - index;
            if (state_nref > 0) {
                index += state_nref - 1;
                index = states.length - 1 - index;
            }
            if (index >= states.length) return;
            return states[index];
        };
        var state_update = function(index) {
            if (states.length <= 0) return;
            if (!index) index = 0;
            if (index >= 0) {
                if (index >= states.length) return;
                var node = states[states.length - 1 - index];
                node.state = state_curr;
                node.count = state_nref;
                node.index = object.index;
                node.value = token;
                return;
            }
            index = -1 - index;
            if (index >= states.length) return;
            var node = states[index];
            node.state = state_curr;
            node.count = state_nref;
            node.index = object.index;
            node.value = token;
        };
        var state_reverse = function() {
            if (state_nref <= 1) return;
            var count = state_nref / 2;
            for (var i = 0; i < count; ++i) {
                var top = state_top(i);
                var bom = state_top(state_nref - i - 1);
                var val = top.value;
                top.value = bom.value;
                bom.value = val;
            }
        }
        var section = function(start, end, curr_prio) {
            var top = state_top();
            var op = top.opera;
            if (op != start) return false;
            if (curr_prio != end) return true;
            var tmp = top.usetmp;
            var val = top.value;
            state_pop(2);
            top = state_top();
            if (top.value == start) {
                top = state_push();
                top.opera = start;
            }
            else top.opera = top.value;
            top.value = val;
            if (tmp) top.usetmp = tmp;
            return true;
        };
        var compute = function(curr_prio) {
            while (state_nref) {
                /// 是区间闭合的话，直接消除并返回
                if (section("(", ")", curr_prio)) break;

                /// 取栈顶的操作符 (栈顶已变为操作数+操作符)
                var top = state_top();
                var op = top.opera;
                var opnode = opt[op];
                var opcount = opnode.count;
                if (opcount > state_nref) break;
                var opargs = [];
                var usetmp = null;
                var srcount = opnode.src;

                /// 获取操作源(参数1-n)，并记录使用的临时参数
                for (var i = 0; i < srcount; ++i) {
                    var top = state_top(srcount-1-i);
                    var val = top.value;
                    opargs[i+1] = val;
                    reg_tmp_ref(val, false);
                    if (!usetmp && top.usetmp) usetmp = val;
                }

                /// 获取操作目的，如果没有指明直接的目的，则需要使用临时参数
                if (opnode.dst) {
                    opargs[0] = state_top(opnode.dst).value;
                }
                else if (usetmp) {
                    opargs[0] = usetmp;
                }
                else {
                    var last = state_top(-1);
                    if (last && (last.opera == "ASSIGN")) {
                        opargs[0] = last.value;
                        last.opera = "VALUED";
                        usetmp = opargs[0];
                    }
                    else {
                        opargs[0] = "r" + reg_tmp_new();
                        usetmp = opargs[0];
                    }
                }

                /// 生成指令，忽略源和目的相同的移位操作
                if ((opnode.name != "mov") || (opargs[0] != opargs[1])) {
                    ins_out(opnode.name, opargs);
                }

                /// 移除操作源，保留操作目的在栈中 (如果目的不是最新临时值，则需要去除最新临时值)
                if (opcount > 1) state_pop(opcount - 1);
                state_top().value = opargs[0];
                if (usetmp) state_top().usetmp = usetmp;

                /// 只有一个操作数时，直接移除
                if (state_nref <= 1) {
                    if (state_nref > 0) state_pop(state_nref);
                    reg_tmp_pop();
                    break;
                }

                /// 目的操作数需要进行临时引用，并去除不使用的临时值
                reg_tmp_ref(state_top().value, true);
                reg_tmp_pop();

                /// 如果是括号，处理后需要直接接收下次闭合
                if (section("(", ")", curr_prio)) break;

                /// 循环进行下一步的计算
                var next_prio = opt[state_top().opera].prio;
                if (curr_prio && (curr_prio < next_prio)) {
                    break;
                }
            }
        };
        var proc = {
            lex_entry: function() {
                if (state_nref > 0) state_pop(state_nref);
                if (token == ";") return;
                var lex_stat = lex[token];
                if (lex_stat) {
                    state_curr = lex_stat;
                    return;
                }
                switch (type) {
                    case "type_var":
                        state_curr = "var_refer";
                        proc[state_curr]();
                        break;
                    case "type_int":
                    case "type_float":
                    case "type_bool":
                    case "type_str":
                        state_curr = "var_rvalue";
                        proc[state_curr]();
                        break;
                    default:
                        state_curr = "run_error";
                        break;
                }
            },
            var_define: function() {
                if (type != "type_var") {
                    state_curr = "run_error";
                    return;
                }
                var reg_idx = vars[token];
                if (!reg_idx) {
                    reg_idx = "r" + reg_push();
                    vars[token] = reg_idx;
                }
                state_push();
                state_top().value = reg_idx;
                state_curr = "var_assign";
            },
            var_refer: function() {
                if (type != "type_var") {
                    state_curr = "run_error";
                    return;
                }
                var reg_idx = vars[token];
                if (!reg_idx) {
                    reg_idx = "r" + reg_push();
                    vars[token] = reg_idx;
                    /// 未定义的变量进入赋值状态
                    state_curr = "var_assign";
                }
                else {
                    /// 已定义的变量进入左值状态
                    state_curr = "var_lvalue";
                }
                state_push();
                state_top().value = reg_idx;
            },
            var_assign: function() {
                switch (token) {
                    case ";":
                        state_curr = "lex_entry";
                        break;
                    case ",":
                        state_curr = "var_define";
                        break;
                    case "=":
                        /// 如果栈中有多个变量需要被赋值，则需要先被反序
                        state_reverse();
                        state_top().opera = "ASSIGN";
                        state_push();
                        state_curr = "var_rvalue";
                        break;
                    default:
                        state_curr = "run_error";
                        break;
                }
            },
            var_lvalue: function() {
                switch (token) {
                    case ";":
                        compute();
                        state_curr = "lex_entry";
                        break;
                    case ",":
                        state_curr = "var_define";
                        break;
                    case "+":
                    case "-":
                    case "*":
                    case "/":
                    case "%":
                    case "<":
                    case ">":
                    case "&":
                    case "^":
                    case "|":
                        state_push();
                        state_curr = "var_operate";
                        break;
                    case "=":
                        state_top().opera = "ASSIGN";
                        state_push();
                        state_curr = "var_rvalue";
                        break;
                    case "(":
                        state_top().opera = "CALL";
                        state_push();
                        state_curr = "var_rvalue";
                        break;
                    default:
                        break;
                }
            },
            var_operate: function() {
                var top = state_top().value;
                if ((top == "<") || (top == ">")) {
                    if (token != top) {
                        state_curr = "run_error";
                        return;
                    }
                    state_top().value += token;
                    return;
                }
                switch (token) {
                    case "=":
                        state_top().value += token;
                        state_curr = "var_rvalue";
                        break;
                    default:
                        state_curr = "run_error";
                        break;
                }
            },
            var_rvalue: function() {
                if (token == "(") {
                    state_push();
                    state_top().opera = op;
                    state_curr = "var_rvalue";
                    return;
                }
                if (type == "type_var") {
                    if (!vars[token]) {
                        state_curr = "run_error";
                        return;
                    }
                    var top = state_top();
                    var op = top.value;
                    if (op == "(") top = state_push();
                    else state_update();
                    top.value = vars[token];
                    top.opera = op;
                    state_curr = "var_continue";
                    return;
                }
                var val;
                switch (type) {
                    case "type_int":
                        val = parseInt(token);
                        break;
                    case "type_float":
                        val = parseFloat(token);
                        break;
                    case "type_bool":
                        val = (token == "true")? true : false;
                        break;
                    case "type_str":
                        val = token;
                        break;
                }
                var top = state_top();
                var op = top.value;
                if (op == "(") top = state_push();
                else state_update();
                top.value = val;
                top.opera = op;
                state_curr = "var_continue";
            },
            var_continue: function() {
                switch (token) {
                    case ";":
                        compute();
                        state_curr = "lex_entry";
                        break;
                    case ",":
                        compute();
                        state_curr = "var_rvalue";
                        break;
                    case "+":
                    case "-":
                    case "*":
                    case "/":
                    case "%":
                    case "&":
                    case "^":
                    case "|":
                        var prev_op = state_top().opera;
                        if (prev_op != "(") {
                            var prev_prio = opt[prev_op].prio;
                            var curr_prio = opt[token].prio;
                            if (curr_prio >= prev_prio) compute(curr_prio);
                        }
                        state_push();
                        state_curr = "var_rvalue";
                        break;
                    case "<":
                    case ">":
                        state_push();
                        state_curr = "var_express";
                        break;
                    case ")":
                        compute(token);
                        break;
                    default:
                        if (type == "type_var") {
                            compute();
                            state_curr = "lex_entry";
                            state_proc(type, token, state);
                        }
                        else {
                            state_curr = "run_error";
                        }
                        break;
                }
            },
            var_express: function() {
                var top = state_top().value;
                if ((top == "<") || (top == ">")) {
                    if (token != top) {
                        state_curr = "run_error";
                        return;
                    }
                    state_top().value += token;
                    state_curr = "var_rvalue";
                    return;
                }
                switch (token) {
                    case "(":
                        break;
                }
            },
            fun_define: function() {
                
            },
            fun_args: function() {
                
            },
            if_define: function() {
                
            },
            for_define: function() {
                
            },
            while_define: function() {
                
            },
            switch_define: function() {
    
            },
            case_define: function() {
    
            },
            continue_define: function() {
    
            },
            break_define: function() {
    
            },
            run_error: function() {
                ins_out("call", {name:"run_error"});
                state_curr = "lex_entry";
            },
        };

        /// 下一个语句开始时，自动添加分号
        if (lex[token] && (state_curr != "lex_entry")) {
            state_proc("type_ctrl", ";", "unkown");
        }

        var lex_proc = proc[state_curr];
        if (lex_proc) lex_proc(type, token);

        /// 解析结束时自动添加分号
        if ((state == "finish") && (state_curr != "lex_entry")) {
            state_proc("type_ctrl", ";", "unkown");
        }

        /// 失败处理
        if (state_curr == "run_error") {
            state_proc("", "", "");
        }

        /// 结束时执行
        if (state == "finish") {
            var ins_pos = 0;
            while (ins_pos < object.codes.length) {
                ins_exe(object.codes[ins_pos]);
                ins_pos++;
            }
            console.log(regs[vars["a"].substring(1)]);
            console.log(regs[vars["b"].substring(1)]);
        }
    };
    var state_change = function(type, i, state) {
        var index = object.index;
        if (i > index) {
            var token = str.substring(index, i);
            state_proc(type, token, state);
        }
        object.state = state;
        object.index = i;
    };

    /// 需要无返回值，否则太复杂，外面只能知道不断循环，for(是固定往前遍历的)；
    /// 如果哪个状态需要倒退，则自行转发到对应的状态机中，并把索引减少。

    var table = {
        init: function(i) {
            if (i >= str.length) {
                object.state = "finish";
                return;
            }
            var a = str[i];
            var b = chr[a];
            object.state = (b)? b : "error";
        },
        finish: function(i) {
            object.index = i;
            return;
        },
        char_lex: function(i) {
            if (i >= str.length) {
                return state_change("type_var", i, "finish");
            }
            var a = str[i];
            var b = chr[a];
            if ((b == "char_lex") || (b == "char_underscore") || 
                (b == "char_num") || (b == "char_zero")) {
                return;
            }
            state_change("type_var", i, (b)? b : "error");
        },
        char_str: function(i) {
            if (i >= str.length) {
                object.state = "error";
                return;
            }
            var a = str[i];
            if (((a == '\'') && (str[object.index] == "\'")) || 
                ((a == '\"') && (str[object.index] == "\""))) {
                state_change("type_str", i + 1, "char_lex");
            }
        },
        char_zero: function(i) {
            if (i >= str.length) {
                return state_change("type_int", i, "finish");
            }
            var a = str[i];
            if ((a == 'x') || (a == 'X')) {
                object.state = "char_hex_x";
                return;
            }
            var b = chr[a];
            if (b == "char_dot") {
                object.state = "char_float_dot";
                return;
            }
            if (b == "char_num") {
                object.index = i;
                object.state = b;
                return;
            }
            if (b == "char_zero") {
                object.index = i;
                return;
            }
            if ((b) && (b != "char_lex") && (b != "char_underscore")) {
                return state_change("type_int", i, b);
            }
            object.state = "error";
        },
        char_num: function(i) {
            if (i >= str.length) {
                return state_change("type_int", i, "finish");
            }
            var a = str[i];
            var b = chr[a];
            if (b == "char_dot") {
                object.state = "char_float";
                return;
            }
            if ((b == "char_num") || (b == "char_zero")) {
                return;
            }
            if ((b) && (b != "char_lex") && (b != "char_underscore")) {
                return state_change("type_int", i, b);
            }
            object.state = "error";
        },
        char_hex_x: function (i) {
            if (i >= str.length) {
                object.state = "error";
                return;
            }
            var a = str[i];
            var h = hex[a];
            if (h) {
                object.state = h;
                return;
            }
            object.state = "error";
        },
        char_hex: function (i) {
            if (i >= str.length) {
                return state_change("type_int", i, "finish");
            }
            var a = str[i];
            var h = hex[a];
            if (h) return; // i + 1;
            var b = chr[a];
            if ((b) && (b != "char_lex") && (b != "char_underscore")) {
                return state_change("type_int", i, b);
            }
            object.state = "error";
        },
        char_float_dot: function(i) {
            if (i >= str.length) {
                object.state = "error";
                return;
            }
            var a = str[i];
            var b = chr[a];
            if ((b == "char_num") || (b == "char_zero")) {
                object.state = "char_float";
                return;
            }
            object.state = "error";
        },
        char_float: function(i) {
            if (i >= str.length) {
                return state_change("type_float", i, "finish");
            }
            var a = str[i];
            var b = chr[a];
            if ((b == "char_num") || (b == "char_zero")) {
                return;
            }
            if ((b) && (b != "char_dot") && (b != "char_lex") && (b != "char_underscore")) {
                return state_change("type_float", i, b);
            }
            object.state = "error";
        },
        char_single_quot: function(i) {
            if (i >= str.length) {
                object.state = "error";
                return;
            }
            var a = str[i];
            if (a == '\'') {
                return state_change("type_str", i + 1, "char_lex");
            }
            else {
                object.state = "char_str";
            }
        },
        char_double_quot: function(i) {
            if (i >= str.length) {
                object.state = "error";
                return;
            }
            var a = str[i];
            if (a == '\"') {
                return state_change("type_str", i + 1, "char_lex");
            }
            else {
                object.state = "char_str";
            }
        },
        char_space: function(i) {
            if (i >= str.length) {
                object.state = "finish";
                return;
            }
            var a = str[i];
            var b = chr[a];
            if (b == "char_space") return (object.index = i + 1);
            object.index = i;
            object.state = (b)? b : "error";
        },
        error: function(i) {
            return;
        },
        unkown: function(i) {
            if (i >= str.length) {
                return state_change("type_ctrl", i, "finish");
            }
            var a = str[i];
            var b = chr[a];
            state_change("type_ctrl", i, (b)? b : "error");
        }
    };

    var len = str.length;
    for (var i = 0; i < len; ++i) {
        if (!table[object.state]) object.state = "unkown";
        table[object.state](i);
        if (object.state == "error") break;
    }

    if (object.state != "finish") {
        if (!table[object.state]) object.state = "unkown";
        table[object.state](len);
    }

    return object;
};



