local M = {
    "stevearc/quicker.nvim",
    event = "FileType qf",
    opts = {},
    config = function()
        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        nmap_leader("qt", function()
            require("quicker").toggle()
        end, "Toggle Quickfix")

        nmap_leader("qp", "<cmd>cprev<cr>", "Prev")
        nmap_leader("qn", "<cmd>cnext<cr>", "Next")
    end,
}

return M
