local M = {
    'nvim-lualine/lualine.nvim',
    dependencies = { 'nvim-tree/nvim-web-devicons' },
    config = function()
        local function get_lsp_client_names()
            local bufnr = vim.api.nvim_get_current_buf()
            -- Use get_clients for Neovim 0.10+ and 0.11
            local clients = vim.lsp.get_clients({ bufnr = bufnr })
            if next(clients) == nil then
                return 'No LSP'
            end
            local client_names = {}
            for _, client in pairs(clients) do
                table.insert(client_names, client.name)
            end
            -- Return icons and server names separated by pipes
            return '   ' .. table.concat(client_names, '|')
        end

        require('lualine').setup({
            sections = {
                lualine_x = {
                    -- Add your custom function here
                    { get_lsp_client_names, color = { fg = '#ffffff', gui = 'bold' } },
                    'filetype'
                },
            }
        })
    end
}

return M;
