from sys import argv


# reserved worlds and symbols
directives = ("segment", "dd", "db", "dw", "ends", "end")
commands = ("jbe", "inc", "dec", "sub", "and", "or", "mov", "cmp", "stc", "push")
registers_32 = ("eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi")
segments = ("es", "cs", "ss", "ds", "fs", "gs")
hex_symbols = ("a", "b", "c", "d", "e", "f")
bin_symbols = ("0", "1")
symbols = ("+", "-", "*", "/", ",", ":", "(", ")", "[", "]")
reg_num = {"eax": 0b000, "ecx": 0b001, "edx": 0b010, "ebx": 0b011, "esp": 0b100, "ebp": 0b101, "esi": 0b110, "edi": 0b111}
seg_num = {"es": "26", "cs": "2E", "ss": "36", "ds": "3E", "fs": "64", "gs": "65"}

lables = []


token_types = {
    directives: "directive",
    commands: "command",
    registers_32: "Register_32bit",
    segments: "segment",
    "hexadecimal": "hexadecimal",
    symbols: "symbols",
    # "identifier": "identifier",
}


def main():
    scanner = Scanner()
    # print("E R R O R S")
    # scanner.lexer()
    # scanner.print_lexical()
    scanner.listing()
    # print("_" * 80)
    # scanner.print_lexical()
    print()
    scanner.second()
    scanner.print_listing()

class Token:
    text = ""
    token_type = ""
    index = 0
    length = 0

    def __str__(self):
        return(f"{self.index:<4}{self.text:^40}\t{self.token_type:^25}{self.length:>5}")


class Scanner:
    current_line = 0
    sentences = []
    segments = {}
    filename = ""
    segment = Token()
    segment.text = ""
    symbols = {}
    offset = 0
    bytes = ""

    def lexer(self, line):
        if not line or line == "\n":
            return []
        index = -1
        i = 0
        lexems = []

        while i < len(line):
            if line[i] == ";":
                break;
            elif line[i].isspace() or line[i] == "\n":
                i += 1
            else:
                index += 1
                lexem = Token()
                lexem.index = index

                if line[i].isalpha():
                    while i < len(line) and (line[i].isalpha() or line[i].isdigit()):
                        lexem.text += line[i]
                        i += 1
                    if lexem.text.lower() in directives:
                        lexem.token_type = token_types[directives]
                    elif lexem.text.lower() in commands:
                        lexem.token_type = token_types[commands]
                    elif lexem.text.lower() in registers_32:
                        lexem.token_type = token_types[registers_32]
                    elif lexem.text.lower() in segments:
                        lexem.token_type = token_types[segments]
                    else:
                        lexem.length = len(lexem.text)
                        if lexem.length > 8:
                            print("Identifier  \"" + lexem.text + "\"  too long")
                            exit(1)
                        lexem.token_type = "identifier"

                        if line[i] == ":":
                            if lexem.text not in lables:
                                lables.append(lexem.text)
                    lexem.length = len(lexem.text)
                    lexems.append(lexem)
                elif line[i].isdigit():
                    while i < len(line) and (line[i].isdigit() or line[i].lower() in hex_symbols or line[i].lower() == "h"):
                        lexem.text += line[i]
                        i += 1
                    if lexem.text[-1].lower() == 'h':
                        for char in lexem.text[:-1]:
                            # Hex number check (if wrong symbol - "exit")
                            if char not in hex_symbols and not char.isdigit():
                                print("Wrong hex number")
                                exit(1)
                        lexem.token_type = "hexadecimal"
                    elif lexem.text[-1].lower() == "b":
                        for char in lexem.text[:-1]:
                        # Bin numer check (if wrong - "exit")
                            if char not in bin_symbols:
                                print("Wrong bin number")
                                exit(1)
                        lexem.token_type = "binary"
                    else:
                        # Decimal numer check (if wrong - "exit")
                        for char in lexem.text:
                            if not char.isdigit():
                                print("Wrong dec number")
                                exit(1)
                        lexem.token_type = "decimal"
                    lexem.length = len(lexem.text)
                    lexems.append(lexem)
                elif line[i] in symbols:
                    lexem.text = line[i]
                    lexem.token_type = token_types[symbols]
                    i += 1
                    lexem.length = len(lexem.text)
                    lexems.append(lexem)
                else:
                    print("Wrong symbol")
                    exit(1)
        return lexems

    def check_mem(self, lexems, iter, sentence):
        lexems_text = []
        for x in lexems:
            lexems_text.append(x.text)

        seg = None
        if lexems[iter].text.lower() in segments:
            seg = lexems[iter].text
            iter += 2
        if lexems[iter].text in self.symbols:
            try:
                if self.symbols.get(lexems[iter].text).type == "L WORD":
                    # print("Cannot use 16bit variable on line number " + str(self.current_line))
                    sentence.error += "Cannot use 16bit variable on line number " + str(self.current_line)
            except KeyError:
                pass
        else:
            print("Undefined operand on line number " + str(self.current_line))

        ident = None
        reg1 = None
        reg2 = None

        if "[" not in lexems_text:
            # print("Wrong operand on line number " + str(self.current_line))
            sentence.error += "Wrong operand on line number " + str(self.current_line)
        elif "]" not in lexems_text:
            # print("Wrong operand on line number " + str(self.current_line))
            sentence.error += "Wrong operand on line number " + str(self.current_line)
        elif lexems[lexems_text.index("[") + 1].text not in registers_32:
            # print("Wrong operand on line number " + str(self.current_line))
            sentence.error += "Wrong operand on line number " + str(self.current_line)
        elif lexems[lexems_text.index("[") + 2].text != "+":
            # print("Wrong operand on line number " + str(self.current_line))
            sentence.error += "Wrong operand on line number " + str(self.current_line)
        elif lexems[lexems_text.index("]") - 1].text not in registers_32:
            # print("Wrong operand on line number " + str(self.current_line))
            sentence.error += "Wrong operand on line number " + str(self.current_line)
        else:
            ident = lexems[iter].text
            reg1 = lexems[lexems_text.index("[") + 1].text
            reg2 = lexems[lexems_text.index("]") - 1].text

        return [seg, ident, reg1, reg2]

    def check_reg(self, lexems, i, sentence):
        reg = None
        if lexems[i].text not in registers_32:
            # print("Wrong operand on line number " + str(self.current_line))
            sentence.error += "Wrong operand on line number " + str(self.current_line)
        else:
            reg = lexems[i].text
        return reg

    def check_imm(self, lexems, i, sentence):
        imm = None
        if i < len(lexems):
            parentheses1 = 0
            parentheses2 = 0
            operand = ""
            while i < len(lexems):
                if lexems[i].text == "(":
                    parentheses1 += 1
                elif lexems[i].text == ")":
                    parentheses2 += 1
                if lexems[i].text[-1].lower() == "b":
                    operand += "0b" + lexems[i].text[0:-1]
                elif lexems[i].text[-1].lower() == "h":
                    operand += "0x" + lexems[i].text[0:-1]
                else:
                    operand += lexems[i].text
                i += 1
            if parentheses1 == parentheses2:
                imm = eval(operand)
                imm = hex(imm)
            else:
                # print("Wrong operand on line number " + str(self.current_line))
                sentence.error += "Wrong operand on line number " + str(self.current_line)

        return imm

    def check_two_operand(self, first_function, second_function, lexems, i, sentence):
        lexems_text = []
        operand1 = None
        operand2 = None
        for x in lexems:
            lexems_text.append(x.text)

        if "," not in lexems_text:
            # print("Need second operand on line number " + str(self.current_line))
            sentence.error += "Need second operand on line number " + str(self.current_line)
        else:
            operand1 = first_function(lexems, i, sentence)
            operand2 = second_function(lexems, lexems_text.index(",") + 1, sentence)

        return [operand1, operand2]

    def listing(self):
        self.filename = argv[1]
        for line in open(argv[1], "r"):
            self.lexer(line)
        for line in open(argv[1], "r"):
            sentence = Sentence(self.lexer(line))
            sentence.source = line
            lexems = sentence.lexems
            self.current_line += 1
            identifier = None
            mnemonic = None
            i = 0

            if i < len(lexems) and lexems[i].token_type == "identifier":
                user_identifier = lexems[i]
                i += 1
                if i < len(lexems):
                    if lexems[i].text == ":":
                        i += 1
                        if i < len(lexems) and lexems[i].text == ":":
                            # print("Extra character on line number " + str(self.current_line))
                            sentence.error += "Extra character on line number " + str(self.current_line)
                            # exit(1)
                        symbol = Symbol()
                        symbol.segment = self.segment
                        symbol.value = "%.4x" % self.offset
                        symbol.type = "L NEAR"
                        self.symbols[user_identifier.text] = symbol
                    else:
                        identifier = user_identifier
                else:
                    identifier = user_identifier

            if i < len(lexems) and (lexems[i].token_type == "directive" or lexems[i].token_type == "command"):
                mnemonic = lexems[i]
                i += 1

            if mnemonic:
                if identifier:
                    if mnemonic.text.lower() == "segment":
                        sentence.printed = True
                        self.offset = 0
                        self.segment = identifier
                    elif mnemonic.text.lower() == "dd":
                        if identifier.text in self.symbols:
                            # print("Multidefined symbol on line number " + str(self.current_line))
                            sentence.error += "Multidefined symbol on line number " + str(self.current_line)
                            # exit(1)
                        sentence.printed = True
                        sentence.length = 4
                        sentence.operands = self.check_imm(lexems, i, sentence)

                        symbol = Symbol()
                        symbol.type = "L DWORD"
                        symbol.value = "%.4x" % self.offset
                        symbol.segment = self.segment

                        if i < len(lexems):
                            i += 1
                        else:
                            # print("No operand on line number " + str(self.current_line))
                            # exit(1)
                            sentence.error += "No operand on line number " + str(self.current_line)
                        self.symbols[identifier.text] = symbol
                    elif mnemonic.text.lower() == "dw":
                        if identifier.text in self.symbols:
                            # print("Multidefined symbol on line number " + str(self.current_line))
                            # exit(1)
                            sentence.error += "Multidefined symbol on line number " + str(self.current_line)
                        sentence.printed = True
                        sentence.length = 2
                        sentence.operands = self.check_imm(lexems, i, sentence)

                        symbol = Symbol()
                        symbol.type = "L WORD"
                        symbol.value = "%.4x" % self.offset
                        symbol.segment = self.segment

                        if i < len(lexems):
                            i += 1
                        else:
                            # print("No operand on line number  " + str(self.current_line))
                            sentence.error += "No operand on line number  " + str(self.current_line)
                            exit(1)

                        self.symbols[identifier.text] = symbol
                    elif mnemonic.text.lower() == "db":
                        if identifier.text in self.symbols:
                            # print("Multidefined symbol on line number " + str(self.current_line))
                            # exit(1)
                            sentence.error += "No operand on line number " + str(self.current_line)
                        sentence.printed = True
                        sentence.length = 1
                        sentence.operands = self.check_imm(lexems, i, sentence)

                        symbol = Symbol()
                        symbol.type = "L BYTE"
                        symbol.value = "%.4x" % self.offset
                        symbol.segment = self.segment

                        if i < len(lexems):
                            i += 1
                        else:
                            # print("No operand on line number " + str(self.current_line))
                            sentence.error += "No operand on line number " + str(self.current_line)
                        self.symbols[identifier.text] = symbol
                    elif mnemonic.text.lower() == "ends":
                        if identifier.text != self.segment.text:
                            # print("Wrong segment name on line number " + str(self.current_line))
                            # exit(1)
                            sentence.error += "Wrong segment name on line number " + str(self.current_line)
                        sentence.printed = True
                        self.segments[identifier.text] = self.offset
                    elif mnemonic.text.lower() == "end":
                        pass
                    else:
                        print(line)
                        # print("Need instruction or directive")
                        sentence.error += "Need instruction or directive"
                        exit(1)
                else:
                    if mnemonic.text.lower() == "jbe":
                        if lexems[i].token_type != "identifier":
                            # print("Wrong operand for jbe on line number " + str(self.current_line))
                            sentence.error += "Wrong operand for jbe on line number " + str(self.current_line)
                        else:
                            if lexems[i].text in self.symbols:
                                sentence.printed = True
                                sentence.length = 2
                                sentence.operands = lexems[i].text
                            else:
                                if lexems[i].text not in lables:
                                    # print("Undentifiend operand on line number " + str(self.current_line))
                                    sentence.error += ("Undentifiend operand on line number " + str(self.current_line))
                                sentence.printed = True
                                sentence.length = 6
                                sentence.operands = lexems[i].text
                    elif mnemonic.text.lower() == "stc":
                        sentence.printed = True
                        sentence.length = 1

                    elif mnemonic.text.lower() == "inc":
                        sentence.operands = self.check_reg(lexems, i, sentence)
                        sentence.printed = True
                        sentence.length = 1

                    elif mnemonic.text.lower() == "dec":
                        sentence.operands = self.check_mem(lexems, i, sentence)
                        if self.symbols.get(lexems[i].text) is not None:
                            if self.symbols.get(lexems[i].text).segment == self.segment:
                                if self.symbols[lexems[i].text].type == "L BYTE":
                                    sentence.printed = True
                                    sentence.length = 8
                                elif self.symbols[lexems[i].text].type == "L WORD":
                                    sentence.printed = True
                                    sentence.length = 9
                                elif self.symbols[lexems[i].text].type == "L DWORD":
                                    sentence.printed = True
                                    sentence.length = 8
                            else:
                                if self.symbols[lexems[i].text].type == "L BYTE":
                                    sentence.printed = True
                                    sentence.length = 7
                                elif self.symbols[lexems[i].text].type == "L WORD":
                                    sentence.printed = True
                                    sentence.length = 8
                                elif self.symbols[lexems[i].text].type == "L DWORD":
                                    sentence.printed = True
                                    sentence.length = 7
                    elif mnemonic.text.lower() == "sub":
                        sentence.operands = self.check_two_operand(self.check_reg, self.check_reg, lexems, i, sentence)
                        sentence.printed = True
                        sentence.length = 2
                    elif mnemonic.text.lower() == "and":
                        sentence.operands = self.check_two_operand(self.check_reg, self.check_mem, lexems, i, sentence)
                        if self.symbols[sentence.operands[1][1]].type != "L DWORD":
                            # print("Operands types must match, on line number " + str(self.current_line))
                            sentence.error += "Operands types must match, on line number " + str(self.current_line)
                            # exit(1)
                        else:
                            sentence.printed = True
                            sentence.length = 7
                    elif mnemonic.text.lower() == "or":
                        sentence.operands= self.check_two_operand(self.check_mem, self.check_imm, lexems, i, sentence)
                        if self.symbols[lexems[i + 2].text].type == "L BYTE":
                            sentence.printed = True
                            sentence.length = 9
                        elif self.symbols[lexems[i + 2].text].type == "L WORD":
                            sentence.printed = True
                            sentence.length = 10
                        elif self.symbols[lexems[i + 2].text].type == "L DWORD":
                            sentence.printed = True
                            sentence.length = 9
                    elif mnemonic.text.lower() == "mov":
                        sentence.operands = self.check_two_operand(self.check_reg, self.check_imm, lexems, i, sentence)
                        sentence.printed = True
                        sentence.length = 5
                    elif mnemonic.text.lower() == "cmp":
                        sentence.operands = self.check_two_operand(self.check_mem, self.check_reg, lexems, i, sentence)
                        if self.symbols[lexems[i].text].type != "L DWORD":
                            # print("Operands types must match, on line number " + str(self.current_line))
                            sentence.error += "Operands types must match, on line number " + str(self.current_line)
                        else:
                            sentence.printed = True
                            sentence.length = 7
                    elif mnemonic.text.lower() == "push":
                        sentence.operands = self.check_imm(lexems, i, sentence)
                        sentence.printed = True
                        sentence.length = 2
            else:
                if identifier:
                    # print("Need command or segment on line number " + str(self.current_line))
                    sentence.error += "Need command or segment on line number " + str(self.current_line)

            sentence.offset = self.offset
            self.offset += sentence.length
            self.sentences.append(sentence)
            # sentence.print_offset()

    def second(self):
        for current in self.sentences:
            if current.mnemo != -1:
                if current.lexems[current.mnemo].text.lower() == "dd":
                    if current.operands:
                        current.bytes = f"{current.operands[2:].upper():0>8}"
                elif current.lexems[current.mnemo].text.lower() == "db":
                    current.bytes = f"{current.operands[2:].upper():8}"
                elif current.lexems[current.mnemo].text.lower() == "dw":
                    current.bytes = f"{current.operands[2:].upper():0>4}"
                elif current.lexems[current.mnemo].text.lower() == "jbe":
                    # current.bytes = "0F 86"
                    # print(current.offset)
                    # print(self.symbols.keys())
                    # print(current.operands)
                    if current.operands in self.symbols:
                        offset = eval("0x" + self.symbols[current.operands].value)
                        # print(offset)
                        if current.offset < offset:
                            current.bytes = "76"
                            buff_string = str(hex(offset - current.offset - 2))
                            current.bytes = current.bytes + " " + buff_string[2:].upper() + " 90"*4
                        else:
                            current.bytes = "76"
                            buff_string = str(hex(0xfe + offset - current.offset))
                            current.bytes = current.bytes + " " + buff_string[2:].upper()
                elif current.lexems[current.mnemo].text.lower() == "stc":
                    current.bytes = "F9"
                elif current.lexems[current.mnemo].text.lower() == "inc":
                    # print(current.operands)
                    if current.operands in reg_num.keys():
                        buff_string = str(hex(0x40 + reg_num[current.operands]))
                        current.bytes = buff_string[2:].upper()
                elif current.lexems[current.mnemo].text.lower() == "dec":
                    current.bytes = ""
                    seg_string = ""
                    if current.operands[0]:
                        seg_string = seg_num[current.operands[0].lower()] + ":"
                    if seg_string:
                        current.bytes += seg_string + " " + "FF "
                    else:
                        current.bytes += seg_string + "FF "
                    buff_string = ""
                    buff_string = str(hex(reg_num[current.operands[2]] + 8 * reg_num[current.operands[3]]))
                    buff_string = buff_string[2:]
                    buff_string = "8C " + f"{buff_string:0<2}"
                    buff_string = f"{buff_string.upper():0<4}"
                    current.bytes += buff_string + " "
                    if current.operands[1] in self.symbols:
                        buff_string = f"{str(self.symbols[current.operands[1]].value).upper():0>8}"
                        current.bytes += buff_string
                        current.bytes += "r"
                    else:
                        buff_string = "00000000"
                        current.bytes += buff_string
                elif current.lexems[current.mnemo].text.lower() == "sub":
                    # print(current.operands)
                    current.bytes = "2B "
                    buff_string = str(hex(0xc0 + 8 * reg_num[current.operands[0]] + reg_num[current.operands[1]]))
                    buff_string = buff_string[2:].upper()
                    current.bytes += buff_string
                elif current.lexems[current.mnemo].text.lower() == "and":
                    current.bytes = ""
                    seg_string = ""
                    if current.operands[1][0]:
                        seg_string = seg_num[current.operands[1][0].lower()] + ":"
                    if seg_string:
                        current.bytes += seg_string + " " + "23 "
                    else:
                        current.bytes += seg_string + "23 "
                    buff_string = str(hex(0x84 + 8 * reg_num[current.operands[0]]))
                    buff_string = f"{buff_string[2:].upper():0<2}"
                    current.bytes += buff_string + " "
                    buff_string = str(hex(reg_num[current.operands[1][2]] + 8 * reg_num[current.operands[1][3]]))
                    buff_string = f"{buff_string[2:].upper():0<2}"
                    current.bytes += buff_string + " "
                    buff_string = f"{str(self.symbols[current.operands[1][1]].value).upper():0>8}"
                    current.bytes += buff_string
                    current.bytes += "r";
                elif current.lexems[current.mnemo].text.lower() == "or":
                    # print(current.operands)
                    current.bytes = ""
                    seg_string = ""
                    if current.operands[0][0]:
                        seg_string = seg_num[current.operands[0][0].lower()] + ":"
                    if seg_string:
                        current.bytes += seg_string + " " + "80 "
                    else:
                        current.bytes += seg_string + "80 "
                    buff_string = str(hex(reg_num[current.operands[0][2]] + 8 * reg_num[current.operands[0][3]]))
                    buff_string = buff_string[2:]
                    buff_string = f"{buff_string:0<2}"
                    current.bytes += buff_string + " 30" + f" {self.symbols[current.operands[0][1]].value:0>8}"
                    current.bytes += "r "
                    current.bytes += f" {current.operands[1][2:].upper():0>2}"
                elif current.lexems[current.mnemo].text.lower() == "mov":
                    buff_string = str(hex(0xb8 + reg_num[current.operands[0]]))
                    current.bytes = buff_string[2:].upper()
                    current.bytes += f" {current.operands[1][2:].upper():0>8}"
                elif current.lexems[current.mnemo].text.lower() == "cmp":
                    current.bytes = ""
                    seg_string = ""
                    if current.operands[0][0]:
                        seg_string = seg_num[current.operands[1][0].lower()] + ":"
                    if seg_string:
                        current.bytes += seg_string + " " + "39 "
                    else:
                        current.bytes += seg_string + "39 "
                    buff_string = str(hex(0x84 + 8 * reg_num[current.operands[1]]))
                    buff_string = f"{buff_string[2:].upper():0<2}"
                    current.bytes += buff_string + " "
                    buff_string = str(hex(reg_num[current.operands[0][2]] + 8 * reg_num[current.operands[0][3]]))
                    buff_string = f"{buff_string[2:].upper():0<2}"
                    current.bytes += buff_string + " "
                    buff_string = f"{str(self.symbols[current.operands[0][1]].value).upper():0>8}"
                    current.bytes += buff_string
                    current.bytes += "r"
                elif current.lexems[current.mnemo].text.lower() == "push":
                    current.bytes = ""
                    # print(hex(eval(current.operands)))
                    if int(eval(current.operands)) <= 0xff:
                        print("1")
                        current.bytes += "6A "
                        buff_string = f"{current.operands[2:].upper():0>2}"
                        current.bytes += buff_string
                    elif int(eval(current.operands))  <= 0xffff:
                        print("2")
                        current.bytes += "68 "
                        buff_string = f"{current.operands[2:].upper():0>4}"
                        current.bytes += buff_string
                        current.error += "Wrong operand(16bit)\n"
                            
                    elif int(eval(current.operands)) <= 0xffffffff:
                        current.bytes += "68 "
                        buff_string = f"{current.operands[2:].upper():0>8}"
                        current.bytes += buff_string




                    # print(current.bytes)
        # for iter in range(len(self.sentences)):
        #     if self.sentences[iter] != -1:
        #         if self.sentences[iter].lexems[self.sentences[iter].mnemo].text == "dd":
        #             self.sentences[iter].bytes = self.sentences[iter].operands
        #             print(self.sentences[iter].bytes)

    def print_lexical(self):
        for sentence in self.sentences:
            sentence.print_lexical()

    def print_listing(self):
        for sentence in self.sentences:
            sentence.print_offset()

        # print(f"{lable_index_str:^20}{mnemonic_index_str:^20}{operand_index_1str:^10}{operand_count_1str:^10}{operand_index_2str:^10}{operand_count_2str:^10}")
        print("\n\n")

        str_name = "N a m e"
        str_size = "Size"
        str_length = "Length"
        str_type = "Type"
        str_value = "Value"
        str_Attr = "Attr"
        str_bit = "32 bit"

        print("Segments:")
        print("#" * 80)
        print(f"{str_name:^40}{str_size:^10}{str_length:^15}" + "\n")
        for segment in sorted(self.segments):
            # print("%-32s\t%-7s\t%-.4X" % (segment, "16 Bit", self.segments[segment]))
            print(f"{segment:<40}{str_bit:^10}{self.segments[segment]:^15x}" + "\n")
        print("#" * 80)

        print("\n")

        print("Symbols:")
        print("✧" * 80)
        print(f"{str_name:^40}{str_type:^15}{str_value:^15}{str_Attr:^15}" + "\n")
        for symbol in sorted(self.symbols):
            print(f"{symbol:<40}{self.symbols[symbol].type:^15}{self.symbols[symbol].value:^15}{self.symbols[symbol].segment.text:^15}")
            print()
        print("✧" * 80)
        print("\n%-32s\tText  %s" % ("Filename", self.filename))


class Sentence:
    printed = False
    source = ""
    error = ""
    prefix = ""
    bytes = ""
    offset = 0
    length = 0
    lexems = []
    operands = []
    label = -1
    mnemo = -1

    def __init__(self, lexems):
        self.label = -1
        self.mnemo = -1
        self.lexems = lexems
        self.operands = []
        i = 0
        # lable check (bad realization)
        if i < len(self.lexems) and self.lexems[i].token_type == "identifier":
            self.label = lexems[i].index
            i += 1
        while i < len(self.lexems) and self.lexems[i].token_type == token_types[symbols]:
            i += 1
        #  mnemonic check (bad realization)
        if i < len(self.lexems) and self.lexems[i].token_type == token_types[directives]:
            self.mnemo = lexems[i].index
            i += 1
        if i < len(self.lexems) and self.lexems[i].token_type == token_types[commands]:
            self.mnemo = lexems[i].index
            i += 1
        # operands check (bad realization)
        while i < len(self.lexems):
            index = i
            while i < len(self.lexems):
                if self.lexems[i].text == ",":
                    break
                i += 1
            self.operands.append([lexems[index].index, i - lexems[index].index])
            i += 1

    def print_lexical(self):
        print("_" * 80)
        lable_str = "Lable"
        mnemonic_str = "Mnemonic"
        operand_1str = "Operand 1"
        operand_2str = "Operand 2"
        print(f"{lable_str:^20}{mnemonic_str:^20}{operand_1str:^20}{operand_2str:^20}")
        lable_index_str = "index"
        mnemonic_index_str = "index"
        operand_index_1str = "index"
        operand_count_1str = "count"
        operand_index_2str = "index"
        operand_count_2str = "count"
        print(f"{lable_index_str:^20}{mnemonic_index_str:^20}{operand_index_1str:^10}{operand_count_1str:^10}{operand_index_2str:^10}{operand_count_2str:^10}")
        operand1_index = self.operands[0][0] if len(self.operands) > 0 else -1
        operand1_count = self.operands[0][1] if len(self.operands) > 0 else 0
        operand2_index = self.operands[1][0] if len(self.operands) > 1 else -1
        operand2_count = self.operands[1][1] if len(self.operands) > 1 else 0
        print(f"{self.label:^20}{self.mnemo:^20}{operand1_index:^10}{operand1_count:^10}{operand2_index:^10}{operand2_count:^10}")
        print("_" * 80)

    def print_file_lexical(self, output_file):
        print("*" * 80, file = output_file)
        lable_str = "Lable"
        mnemonic_str = "Mnemonic"
        operand_1str = "Operand 1"
        operand_2str = "Operand 2"
        print(f"{lable_str:^20}{mnemonic_str:^20}{operand_1str:^20}{operand_2str:^20}", file = output_file)
        lable_index_str = "index"
        mnemonic_index_str = "index"
        operand_index_1str = "index"
        operand_count_1str = "count"
        operand_index_2str = "index"
        operand_count_2str = "count"
        print(f"{lable_index_str:^20}{mnemonic_index_str:^20}{operand_index_1str:^10}{operand_count_1str:^10}{operand_index_2str:^10}{operand_count_2str:^10}", file = output_file)
        operand1_index = self.operands[0][0] if len(self.operands) > 0 else -1
        operand1_count = self.operands[0][1] if len(self.operands) > 0 else 0
        operand2_index = self.operands[1][0] if len(self.operands) > 1 else -1
        operand2_count = self.operands[1][1] if len(self.operands) > 1 else 0
        print(f"{self.label:^20}{self.mnemo:^20}{operand1_index:^10}{operand1_count:^10}{operand2_index:^10}{operand2_count:^10}", file = output_file)
        print("*" * 80, file = output_file)

    def print_offset(self):
        if self.printed:
            # string = "%4x" % self.offset
            # string = string.replace(" ", "0")
            print(f"{self.offset:0>4x}", end = "")
        elif self.prefix and self.prefix.strip():
            print(self.prefix)
        else:
            if ":" in self.source.rstrip():
                string = "%4x" % self.offset
                print(string.replace(" ", "0"), end="")

        # if self.bytes and self.bytes.strip():
        print(f"{self.bytes:^30}", end = "")

        # print("\t\t%s" % self.source.rstrip())
        print(f"{self.source.rstrip():80}")
        if self.error:
            print(f"{self.error}")


class Symbol:
    segment = ""
    value = ""
    type = ""


if __name__ == "__main__":
    main()