local M = {
    "neovim/nvim-lspconfig",
    dependencies = {
        "williamboman/mason.nvim",
        { "williamboman/mason-lspconfig.nvim" },
        "rachartier/tiny-inline-diagnostic.nvim",
        "hrsh7th/nvim-cmp",
        "hrsh7th/cmp-nvim-lsp",
        "hrsh7th/cmp-buffer",
        "hrsh7th/cmp-path",
        "hrsh7th/cmp-cmdline",
        "hrsh7th/cmp-git",
        "L3MON4D3/LuaSnip",
        "saadparwaiz1/cmp_luasnip",
        "onsails/lspkind.nvim",
        "j-hui/fidget.nvim",
        "windwp/nvim-autopairs",
    },
    config = function()
        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        require("mason").setup()
        require("mason-lspconfig").setup({
            ensure_installed = { "lua_ls", "rust_analyzer", "bashls", "clangd", "jsonls", "pyright", "neocmake" },
            automatic_enable = true
        })

        require("fidget").setup({})

        local cmp = require("cmp")
        local cmp_lsp = require("cmp_nvim_lsp")
        local lspkind = require("lspkind")

        local capabilities = vim.tbl_deep_extend(
            "force",
            {},
            vim.lsp.protocol.make_client_capabilities(),
            cmp_lsp.default_capabilities()
        )

        vim.lsp.config('*', {
            capabilities = capabilities,
        })

        vim.lsp.config("lua_ls", {
            capabilities = capabilities,
            settings = {
                Lua = {
                    diagnostics = {
                        globals = { "vim", "it", "describe", "before_each", "after_each" },
                    },
                },
            }
        })

        vim.lsp.config("clangd", {
            capabilities = capabilities,
            cmd = {
                "clangd",
                "--background-index",
                "-j=4",
                "--clang-tidy",
                "--all-scopes-completion",
                "--cross-file-rename",
                "--completion-style=detailed",
                "--header-insertion-decorators",
                "--header-insertion=iwyu",
                "--pch-storage=memory",
            },
            diagnostics = {
                globals = { "vim" },
            },
        })

        vim.lsp.config("cmake", {
            capabilities = capabilities,
            diagnostics = {
                globals = { "vim" },
            },
        })

        cmp.setup({
            snippet = {
                expand = function(args)
                    require("luasnip").lsp_expand(args.body) -- For `luasnip` users.
                end,
            },
            window = {
                completion = cmp.config.window.bordered(),
                documentation = cmp.config.window.bordered(),
            },
            mapping = cmp.mapping.preset.insert({
                ["C-b"] = cmp.mapping.scroll_docs(-4),
                ["C-f"] = cmp.mapping.scroll_docs(4),
                ["C-e"] = cmp.mapping.abort(),
                ["<S-Tab>"] = cmp.mapping(function(fallback)
                    if cmp.visible() then
                        cmp.select_prev_item()
                    elseif require("luasnip").jumpable(-1) then
                        require("luasnip").jump(-1)
                    else
                        fallback()
                    end
                end, { "i", "s" }),
                ["<Tab>"] = cmp.mapping(function(fallback)
                    if cmp.visible() then
                        cmp.select_next_item()
                    elseif require("luasnip").expand_or_jumpable() then
                        require("luasnip").expand_or_jump()
                    else
                        fallback()
                    end
                end, { "i", "s" }),
                ["<CR>"] = cmp.mapping.confirm({ select = true }),
                ["<C-Space>"] = cmp.mapping.complete(),
            }),
            formatting = {
                format = function(entry, vim_item)
                    local kind_formatter = lspkind.cmp_format({
                        mode = 'text',
                        maxwidth = 120,
                        ellipsis_char = '...',
                    })
                    vim_item = kind_formatter(entry, vim_item)

                    vim_item.menu = ({
                        nvim_lsp = "[LSP]",
                        luasnip  = "[Snippet]",
                        buffer   = "[Buffer]",
                        path     = "[Path]",
                    })[entry.source.name]

                    return vim_item
                end,
            },
            sources = cmp.config.sources({
                { name = "nvim_lsp" },
                { name = "luasnip" },
                { name = "path" },
            }, {
                { name = "buffer" },
            }),
        })

        local cmp_autopairs = require("nvim-autopairs.completion.cmp")
        cmp.event:on("confirm_done", cmp_autopairs.on_confirm_done())

        require("cmp_git").setup()

        cmp.setup.filetype("gitcommit", {
            sources = cmp.config.sources({
                { name = "git" },
            }, {
                { name = "buffer" },
            }),
        })

        cmp.setup.cmdline({ "/", "?" }, {
            mapping = cmp.mapping.preset.cmdline(),
            sources = {
                { name = "buffer" },
            },
        })

        cmp.setup.cmdline(":", {
            mapping = cmp.mapping.preset.cmdline(),
            sources = cmp.config.sources({
                { name = "path" },
            }, {
                { name = "cmdline" },
            }),
            matching = { disallow_symbol_nonprefix_matching = false },
        })

        vim.api.nvim_create_autocmd("LspAttach", {
            group = vim.api.nvim_create_augroup("user_lsp_attach", { clear = true }),
            callback = function(event)
                local opts = { buffer = event.buf }

                nmap_leader("lD", function()
                    vim.lsp.buf.declaration(opts)
                end, "Declaration")


                nmap_leader("ld", function()
                    vim.lsp.buf.definition(opts)
                end, "Definition")

                nmap_leader("li", function()
                    vim.lsp.buf.implementation(opts)
                end, "Implementation")

                nmap_leader("lr", function()
                    vim.lsp.buf.references(opts)
                end, "References")

                nmap_leader("ls", function()
                    vim.lsp.buf.workspace_symbol(opts)
                end, "Symbol")

                nmap_leader("lp", function()
                    vim.diagnostic.goto_prev(opts)
                end, "Prev Error")

                nmap_leader("ln", function()
                    vim.diagnostic.goto_next(opts)
                end, "Next Error")

                nmap_leader("lz", function()
                    vim.diagnostic.open_float(opts)
                end, "Open Diagnostics")

                nmap_leader("la", function()
                    vim.lsp.buf.code_action(opts)
                end, "Code Action")

                nmap_leader("le", function()
                    vim.lsp.buf.rename(opts)
                end, "Rename")

                nmap_leader("lh", function()
                    vim.lsp.buf.signature_help(opts)
                end, "Signature Help")

                nmap_leader("lq", function()
                    vim.lsp.buf.code_action({
                        only = { "quickfix" },
                    })
                end, "Quickfix")

                nmap_leader("lx", "<Cmd>:ClangdSwitchSourceHeader<Cr>", "Switch Header")
            end,
        })
        require("tiny-inline-diagnostic").setup({
            preset = "powerline"
        })
        vim.diagnostic.config({
            virtual_text = false,
            signs = {

                text = {
                    [vim.diagnostic.severity.ERROR] = " ",
                    [vim.diagnostic.severity.WARN] = " ",
                    [vim.diagnostic.severity.INFO] = " ",
                    [vim.diagnostic.severity.HINT] = "",
                },
                numhl = {
                    [vim.diagnostic.severity.ERROR] = "DiagnosticSignError",
                    [vim.diagnostic.severity.WARN] = "DiagnosticSignWarn",
                    [vim.diagnostic.severity.INFO] = "DiagnosticSignInfo",
                    [vim.diagnostic.severity.HINT] = "DiagnosticSignHint",
                },
                texthl = {
                    [vim.diagnostic.severity.ERROR] = "DiagnosticSignError",
                    [vim.diagnostic.severity.WARN] = "DiagnosticSignWarn",
                    [vim.diagnostic.severity.INFO] = "DiagnosticSignInfo",
                    [vim.diagnostic.severity.HINT] = "DiagnosticSignHint",
                },
            },
        })
    end,
}

return M
