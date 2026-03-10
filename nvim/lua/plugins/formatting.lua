local M = {
    "stevearc/conform.nvim",
    opts = {},
    config = function()
        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end
        local xmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("x", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        vim.b.disable_autoformat = true
        vim.g.disable_autoformat = true

        require("conform").setup({
            format_on_save = function(bufnr)
                -- Disable with a global or buffer-local variable
                if vim.g.disable_autoformat or vim.b[bufnr].disable_autoformat then
                    return
                end
                return { timeout_ms = 500, lsp_format = "fallback" }
            end,
            formatters_by_ft = {
                python = { "isort", "black" },
                cpp = { "clang-format" },
                lua = { "stylua" },
            },
        })

        nmap_leader("cfe", "<Cmd>FormatEnable<cr>", "Format Enable")
        nmap_leader("cfd", "<Cmd>FormatDisable<cr>", "Format Disable")
    end,
}

vim.api.nvim_create_user_command("FormatDisable", function(args)
    if args.bang then
        -- FormatDisable! will disable formatting just for this buffer
        vim.b.disable_autoformat = true
    else
        vim.g.disable_autoformat = true
    end
end, {
    desc = "Disable autoformat-on-save",
    bang = true,
})
vim.api.nvim_create_user_command("FormatEnable", function()
    vim.b.disable_autoformat = false
    vim.g.disable_autoformat = false
end, {
    desc = "Re-enable autoformat-on-save",
})

return M
