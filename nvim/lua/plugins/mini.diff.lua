local M = {
    "echasnovski/mini.diff",
    version = false,

    config = function()
        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        require("mini.diff").setup()

        nmap_leader("<leader>go", function()
            MiniDiff.toggle_overlay()
        end, "Toggle Diff Overlay")
    end,
}

return M
