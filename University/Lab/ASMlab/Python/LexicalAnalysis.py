from sys import argv


# reserved worlds and symbols
directives = ("segment", "dd", "db", "dw", "ends", "end")
commands = ("jbe", "inc", "dec", "sub", "and", "or", "mov", "cmp")
registers_32 = ("ebx", "esi", "eax", "ecx", "edx", "ebp")
segments = ("es")
hex_symbols = ("a", "b", "c", "d", "e", "f")
bin_symbols = ("0", "1")
symbols = ("+", "-", "*", "/", ",", ":", "(", ")", "[", "]")


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
    if len(argv) == 2:
        output_file = open("output.txt", "w")
        scanner_object = scanner()
        sentence = Sentence()
        for line in open(argv[1]):
            if scanner_object.lexer(line) is not None:
                # print('\x1b[0;33;33m', end = "")
                # print("_" * 80)
                print("_" * 80, file = output_file)
                # print(line.rstrip())
                print(line.rstrip(), file = output_file)
                # print("_" * 80)
                print("_" * 80, file = output_file)
                # print('\x1b[0m', end = "")
                lexer_list = scanner_object.lexer(line)
                sentence.start(lexer_list)
                sentence.print_file_Lexical(output_file)
                for x in lexer_list:
                    # print(x)
                    print(x, file = output_file)
        output_file.close()
    else: exit(1)


class token:
    text = ""
    token_type = ""
    index = 0
    length = 0

    def __str__(self):
        return(f"{self.index:<4}{self.text:^40}\t{self.token_type:^25}{self.length:>5}")


class scanner:
    current_line = 0
    directives = []
    lexems = []

    def lexer(self, line):
        if not line or line == "\n":
            return None
        index = -1
        i = 0
        lexems = []

        while i < len(line):
            if line[i].isspace() or line[i] == "\n":
                i += 1
            else:
                index += 1
                lexem = token()
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
                        lexem.token_type = "identifier"
                    lexem.length = len(lexem.text)
                    lexems.append(lexem)
                elif line[i].isdigit():
                    while i < len(line) and (line[i].isdigit() or line[i].lower() in hex_symbols or line[i] is "h"):
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


class Sentence:
    lexems = []
    operands = []
    label = -1
    mnemo = -1

    def start(self, lexems):
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
            while (i < len(self.lexems)):
                if self.lexems[i].text == ",":
                    break
                i += 1
            self.operands.append([lexems[index].index, i - lexems[index].index])
            i += 1

    def print_Lexical(self):
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

    def print_file_Lexical(self, output_file):
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



if __name__ == "__main__":
    main()