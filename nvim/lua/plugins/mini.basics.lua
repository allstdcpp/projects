local M = {
    "echasnovski/mini.basics",
    config = function()
        require("mini.basics").setup({
            mappings = {
                windows = false,
                move_with_alt = true
            }
        })
    end,
}

return M
