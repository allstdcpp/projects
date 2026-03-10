local M = {
    "echasnovski/mini-git",
    version = false,
    main = "mini.git",
    config = function()

        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        require("mini.git").setup()

    end,
}

return M
