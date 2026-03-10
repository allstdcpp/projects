return {
    'nvim-telescope/telescope.nvim', tag = 'v0.2.0',
      dependencies = { 'nvim-lua/plenary.nvim' },
      config = function()
      require('telescope').setup{}
        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        nmap_leader("ff", "<Cmd>Telescope find_files<cr>", "Find Files");
        nmap_leader("fb", "<Cmd>Telescope buffers<cr>", "Find Buffers");
        nmap_leader("fg", "<Cmd>Telescope live_grep<cr>", "Grep Files");
      end
    }
