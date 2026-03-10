local M = {
    "lukas-reineke/indent-blankline.nvim",
    main = "ibl",
    opts = {
        scope = {
            enabled = false,
        },
        exclude = {
            filetypes = {
                "terminal",
            },
        },
    },
}

return M
