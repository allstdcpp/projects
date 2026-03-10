function _G.get_oil_winbar()
    local dir = require("oil").get_current_dir()
    if dir then
        return vim.fn.fnamemodify(dir, ":~")
    else
        -- If there is no current directory (e.g. over ssh), just show the buffer name
        return vim.api.nvim_buf_get_name(0)
    end
end

local M = {
    "stevearc/oil.nvim",
    opts = {},
    dependencies = { "echasnovski/mini.icons"},
    config = function()

        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        local detail = false
        local oil = require("oil")
        oil.setup({
            win_options = {
                winbar = "%!v:lua.get_oil_winbar()",
            },
            keymaps = {
                ["gd"] = {
                    desc = "Toggle file detail view",
                    callback = function()
                        detail = not detail
                        if detail then
                            require("oil").set_columns({ "icon", "permissions", "size", "mtime" })
                        else
                            require("oil").set_columns({ "icon" })
                        end
                    end,
                },
            },
        })
        nmap_leader("fo", "<cmd>Oil<cr>","Oil")
    end,
}

return M
