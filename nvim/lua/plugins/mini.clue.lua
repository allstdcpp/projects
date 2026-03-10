local M = {
    "echasnovski/mini.clue",
    config = function()

        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end
        local xmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("x", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        local clue = require("mini.clue")
        clue.setup({
            window = {
                delay = 300,
                config = { width = "auto", border = "single" },
            },
            triggers = {
                -- Leader triggers
                { mode = "n", keys = "<Leader>" },
                { mode = "x", keys = "<Leader>" },

                -- Built-in completion
                { mode = "i", keys = "<C-x>" },

                -- `g` key
                { mode = "n", keys = "g" },
                { mode = "x", keys = "g" },

                -- `[]` keys
                { mode = "n", keys = "[" },
                { mode = "n", keys = "]" },

                -- `\` key
                { mode = "n", keys = [[\]] },

                -- Marks
                { mode = "n", keys = "'" },
                { mode = "n", keys = "`" },
                { mode = "x", keys = "'" },
                { mode = "x", keys = "`" },

                -- Registers
                { mode = "n", keys = '"' },
                { mode = "x", keys = '"' },
                { mode = "i", keys = "<C-r>" },
                { mode = "c", keys = "<C-r>" },

                -- Window commands
                { mode = "n", keys = "<C-w>" },

                -- `z` key
                { mode = "n", keys = "z" },
                { mode = "x", keys = "z" },
            },

            clues = {
                { mode = "n", keys = "gz", desc = "Surround" },

                -- Enhance this by adding descriptions for <Leader> mapping groups
                { mode = "n", keys = "<leader>a", desc = "AI" },
                { mode = "n", keys = "<leader>c", desc = "Code" },
                { mode = "n", keys = "<leader>d", desc = "Debug" },
                { mode = "n", keys = "<leader>f", desc = "Files" },
                { mode = "n", keys = "<leader>g", desc = "Git/diff" },
                { mode = "n", keys = "<leader>l", desc = "LSP" },
                { mode = "n", keys = "<leader>q", desc = "Quit/session" },
                { mode = "n", keys = "<leader>b", desc = "Buffers" },

                -- Bracketed.
                { mode = "n", keys = "]b", postkeys = "]" },
                { mode = "n", keys = "[b", postkeys = "[" },
                { mode = "n", keys = "]c", postkeys = "]" },
                { mode = "n", keys = "[c", postkeys = "[" },
                { mode = "n", keys = "]d", postkeys = "]" },
                { mode = "n", keys = "[d", postkeys = "[" },
                { mode = "n", keys = "]h", postkeys = "]" },
                { mode = "n", keys = "[h", postkeys = "[" },
                { mode = "n", keys = "]q", postkeys = "]" },
                { mode = "n", keys = "[q", postkeys = "[" },
                { mode = "n", keys = "]t", postkeys = "]" },
                { mode = "n", keys = "[t", postkeys = "[" },
                { mode = "n", keys = "]u", postkeys = "]" },
                { mode = "n", keys = "[u", postkeys = "[" },
                { mode = "n", keys = "]w", postkeys = "]" },
                { mode = "n", keys = "[w", postkeys = "[" },
                { mode = "n", keys = "]y", postkeys = "]" },
                { mode = "n", keys = "[y", postkeys = "[" },

                clue.gen_clues.builtin_completion(),
                clue.gen_clues.g(),
                clue.gen_clues.marks(),
                clue.gen_clues.registers(),
                clue.gen_clues.windows({ submode_resize = true }),
                clue.gen_clues.z(),
            },
        })
        nmap_leader("bf", "<Cmd>bfirst<cr>", "First")
        nmap_leader("bp", "<Cmd>bprev<cr>", "Previous")
        nmap_leader("bn", "<Cmd>bnext<cr>", "Next")
        nmap_leader("bl", "<Cmd>blast<cr>", "Last")
        nmap_leader("bd", "<Cmd>bdelete<cr>", "Delete")
        nmap_leader("bk", "<Cmd>bdelete<cr>", "Kill")
    end,
}

return M
