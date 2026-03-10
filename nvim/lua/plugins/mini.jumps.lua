local M = {
    "echasnovski/mini.jump",
    config = function()
        require("mini.jump").setup({
            mappings = {
                forward = "f",
                backward = "F",
                forward_till = "t",
                backward_till = "T",
                repeat_jump = " ",
            },
        })
    end,
}

return M
