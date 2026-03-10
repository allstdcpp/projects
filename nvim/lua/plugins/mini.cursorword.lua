local M = {
    "echasnovski/mini.cursorword",
    config = function()
        require("mini.cursorword").setup({
            delay = 100
        })
    end,
}

return M
