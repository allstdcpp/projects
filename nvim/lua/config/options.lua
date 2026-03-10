-- Hide deprecation warnings
vim.g.deprecation_warnings = false

local opt = vim.opt

opt.autowrite = true -- Enable auto write

-- only set clipboard if not in ssh, to make sure the OSC 52
-- integration works automatically. Requires Neovim >= 0.10.0
opt.clipboard = vim.env.SSH_TTY and "" or "unnamedplus" -- Sync with system clipboard
opt.confirm = true -- Confirm to save changes before exiting modified buffer
opt.cursorline = true -- Enable highlighting of the current line
opt.expandtab = true -- Use spaces instead of tabs
opt.fillchars = {
    foldopen = "",
    foldclose = "",
    fold = " ",
    foldsep = " ",
    diff = "╱",
    eob = " ",
}
opt.ignorecase = true -- Ignore case
opt.showmatch = true -- Show match
opt.linebreak = true -- Wrap lines at convenient points
opt.mouse = "a" -- Enable mouse mode
opt.number = true -- Print line number
opt.relativenumber = true -- Relative line numbers
opt.ruler = false -- Disable the default ruler
opt.scrolloff = 4 -- Lines of context
opt.shiftround = true -- Round indent
opt.shiftwidth = 4 -- Size of an indent
opt.signcolumn = "yes" -- Always show the signcolumn, otherwise it would shift the text each time
opt.smartcase = true -- Don't ignore case with capitals
opt.smartindent = true -- Insert indents automatically
opt.spelllang = { "en" }
opt.tabstop = 4 -- Number of spaces tabs count for
opt.softtabstop = 4 -- Number of spaces tabs count for
opt.termguicolors = true -- True color support
opt.timeoutlen = 500 -- Lower than default (1000)
opt.undofile = true
opt.undolevels = 10000
opt.history = 1000
opt.ttyfast = true
opt.incsearch = true
opt.hlsearch = false
opt.backup = false
opt.writebackup = false
opt.swapfile = false
opt.encoding = "utf-8"
opt.updatetime = 500 -- Save swap file and trigger CursorHold
opt.winminwidth = 5 -- Minimum window width
opt.wrap = false -- Disable line wrap

vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1
