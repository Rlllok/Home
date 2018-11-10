set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'tpope/vim-fugitive'
Plugin 'git://git.wincent.com/command-t.git'

" Schemes
Plugin 'morhetz/gruvbox'
Plugin 'marcopaganini/termschool-vim-theme'
Plugin 'AlessandroYorba/Sierra'

Plugin 'terryma/vim-multiple-cursors'

Plugin 'scrooloose/nerdtree'

Plugin 'itchyny/lightline.vim'

Plugin 'Valloric/YouCompleteMe'

call vundle#end()            " required
filetype plugin indent on    " required


"TAB settings
set tabstop=4 "numbers of visual spaces per TAB
set softtabstop=4 "number of 	spaces in tab when editing
set expandtab " tabs are spaces

"UI settings
syntax enable
let g:sierra_Midnight=1
colorscheme sierra "them
set number "Lines number
" set cursorline "highlight current line
" filetype indent on "load filetype-specific indent files
set wildmenu "autocomplete for command menu
set lazyredraw " redraw only when need to
set showmatch " highlight matching {}

" LightLine
set laststatus=2
let g:lightline = {
      \ 'colorscheme': 'wombat',
      \ 'active': {
      \   'left': [ [ 'mode', 'paste' ],
      \             [ 'readonly', 'filename', 'modified', 'helloworld' ] ]
      \ },
      \ 'component': {
      \ },
      \ }

"Searching settings
set incsearch
set hlsearch
nnoremap <leader><space> :nohlsearch<CR> " /<space> - nohighlight search

"Folding
set foldenable
set foldlevelstart=10 " open most folds by default
set foldnestmax=10 " 10 nested max
nnoremap <space> za " space open/closes fold
" set foldmethod = indent " fold based on indent level

" Movement
nnoremap j gj
nnoremap k gk

nnoremap B ^
nnoremap E $
nnoremap $ <nop>
nnoremap ^ <nop>

"Leader settings
let mapleader = "," " leader is comma

" TMUX settings
" allows cursor change in tmux mode
if exists('$TMUX')
    let &t_SI = "\<Esc>Ptmux;\<Esc>\<Esc>]50;CursorShape=1\x7\<Esc>\\"
    let &t_EI = "\<Esc>Ptmux;\<Esc>\<Esc>]50;CursorShape=0\x7\<Esc>\\"
else
    let &t_SI = "\<Esc>]50;CursorShape=1\x7"
    let &t_EI = "\<Esc>]50;CursorShape=0\x7"
endif
