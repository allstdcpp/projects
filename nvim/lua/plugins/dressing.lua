local M = {
    "stevearc/dressing.nvim",
    config = function()
        require("dressing").setup({
            input = {
                enabled = true,
                default_prompt = "Input: ",
                trim_prompt = true,
                title_pos = "left",
                insert_only = true,
                relative = "cursor",
            },
            select = {
                enabled = true,
                backend = { "telescope", "builtin" },
            },
        })
    end,
}

return M
