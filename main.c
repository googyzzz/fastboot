void udelay(unsigned int usec) {
    unsigned int time = 0, target_time = 0;

    time = (*(volatile unsigned int *) (0x60005010));
    target_time = time + usec;

    if (target_time < usec) {   // check for overflow
        while (time < 0xFFFFFFFF) {
            time = (*(volatile unsigned int *) (0x60005010));
        }
    }
    while (time < target_time) {
        time = (*(volatile unsigned int *) (0x60005010));
    }
}

void clock_set_enable(int periph_id, int enable) {
    unsigned int clk;
    unsigned int reg;

    /* Enable/disable the clock to this peripheral */
    if ((int) periph_id < (int) 96)
        clk = 0x60006000 + 0x10 + (((periph_id < 96) ? ((periph_id) >> 5) : ((periph_id - 96) >> 5)) * 4);
    else
        clk = 0x60006000 + 0x360 + (((periph_id < 96) ? ((periph_id) >> 5) : ((periph_id - 96) >> 5)) * 4);
    reg = (*(volatile unsigned int *) (clk));
    if (enable)
        reg |= (1 << ((periph_id) & 0x1f));
    else
        reg &= ~(1 << ((periph_id) & 0x1f));

    (*(volatile unsigned int *) (clk)) = reg;
}

#define NONE(name) (-1)

enum periphc_internal_id {
    /* 0x00 */
    PERIPHC_I2S1,
    PERIPHC_I2S2,
    PERIPHC_SPDIF_OUT,
    PERIPHC_SPDIF_IN,
    PERIPHC_PWM,
    PERIPHC_05h,
    PERIPHC_SBC2,
    PERIPHC_SBC3,

    /* 0x08 */
    PERIPHC_08h,
    PERIPHC_I2C1,
    PERIPHC_I2C5,
    PERIPHC_0bh,
    PERIPHC_0ch,
    PERIPHC_SBC1,
    PERIPHC_DISP1,
    PERIPHC_DISP2,

    /* 0x10 */
    PERIPHC_10h,
    PERIPHC_11h,
    PERIPHC_VI,
    PERIPHC_13h,
    PERIPHC_SDMMC1,
    PERIPHC_SDMMC2,
    PERIPHC_G3D,
    PERIPHC_G2D,

    /* 0x18 */
    PERIPHC_18h,
    PERIPHC_SDMMC4,
    PERIPHC_VFIR,
    PERIPHC_1Bh,
    PERIPHC_1Ch,
    PERIPHC_HSI,
    PERIPHC_UART1,
    PERIPHC_UART2,

    /* 0x20 */
    PERIPHC_HOST1X,
    PERIPHC_21h,
    PERIPHC_22h,
    PERIPHC_HDMI,
    PERIPHC_24h,
    PERIPHC_25h,
    PERIPHC_I2C2,
    PERIPHC_EMC,

    /* 0x28 */
    PERIPHC_UART3,
    PERIPHC_29h,
    PERIPHC_VI_SENSOR,
    PERIPHC_2bh,
    PERIPHC_2ch,
    PERIPHC_SBC4,
    PERIPHC_I2C3,
    PERIPHC_SDMMC3,

    /* 0x30 */
    PERIPHC_UART4,
    PERIPHC_UART5,
    PERIPHC_VDE,
    PERIPHC_OWR,
    PERIPHC_NOR,
    PERIPHC_CSITE,
    PERIPHC_I2S0,
    PERIPHC_DTV,

    /* 0x38 */
    PERIPHC_38h,
    PERIPHC_39h,
    PERIPHC_3ah,
    PERIPHC_3bh,
    PERIPHC_MSENC,
    PERIPHC_TSEC,
    PERIPHC_3eh,
    PERIPHC_OSC,

    PERIPHC_VW_FIRST,
    /* 0x40 */
    PERIPHC_40h = PERIPHC_VW_FIRST,
    PERIPHC_MSELECT,
    PERIPHC_TSENSOR,
    PERIPHC_I2S3,
    PERIPHC_I2S4,
    PERIPHC_I2C4,
    PERIPHC_SBC5,
    PERIPHC_SBC6,

    /* 0x48 */
    PERIPHC_AUDIO,
    PERIPHC_49h,
    PERIPHC_DAM0,
    PERIPHC_DAM1,
    PERIPHC_DAM2,
    PERIPHC_HDA2CODEC2X,
    PERIPHC_ACTMON,
    PERIPHC_EXTPERIPH1,

    /* 0x50 */
    PERIPHC_EXTPERIPH2,
    PERIPHC_EXTPERIPH3,
    PERIPHC_52h,
    PERIPHC_I2CSLOW,
    PERIPHC_SYS,
    PERIPHC_55h,
    PERIPHC_56h,
    PERIPHC_57h,

    /* 0x58 */
    PERIPHC_58h,
    PERIPHC_59h,
    PERIPHC_5ah,
    PERIPHC_5bh,
    PERIPHC_SATAOOB,
    PERIPHC_SATA,
    PERIPHC_HDA,        /* 0x428 */
    PERIPHC_5fh,

    PERIPHC_X_FIRST,
    /* 0x60 */
    PERIPHC_XUSB_CORE_HOST = PERIPHC_X_FIRST,   /* 0x600 */
    PERIPHC_XUSB_FALCON,
    PERIPHC_XUSB_FS,
    PERIPHC_XUSB_CORE_DEV,
    PERIPHC_XUSB_SS,
    PERIPHC_CILAB,
    PERIPHC_CILCD,
    PERIPHC_CILE,

    /* 0x68 */
    PERIPHC_DSIA_LP,
    PERIPHC_DSIB_LP,
    PERIPHC_ENTROPY,
    PERIPHC_DVFS_REF,
    PERIPHC_DVFS_SOC,
    PERIPHC_TRACECLKIN,
    PERIPHC_ADX0,
    PERIPHC_AMX0,

    /* 0x70 */
    PERIPHC_EMC_LATENCY,
    PERIPHC_SOC_THERM,
    PERIPHC_72h,
    PERIPHC_73h,
    PERIPHC_74h,
    PERIPHC_75h,
    PERIPHC_VI_SENSOR2,
    PERIPHC_I2C6,

    /* 0x78 */
    PERIPHC_78h,
    PERIPHC_EMC_DLL,
    PERIPHC_HDMI_AUDIO,
    PERIPHC_CLK72MHZ,
    PERIPHC_ADX1,
    PERIPHC_AMX1,
    PERIPHC_VIC,
    PERIPHC_7fh,

    PERIPHC_COUNT,

    PERIPHC_NONE = -1,
};

static signed char periph_id_to_internal_id[192] = {
    /* Low word: 31:0 */
    NONE(CPU),
    NONE(COP),
    NONE(TRIGSYS),
    NONE(ISPB),
    NONE(RESERVED4),
    NONE(TMR),
    0x1E,
    0x1F,  /* and vfir 0x68 */

    /* 8 */
    NONE(GPIO),
    0x15,
    0x03,
    PERIPHC_I2S1,
    PERIPHC_I2C1,
    NONE(RESERVED13),
    PERIPHC_SDMMC1,
    PERIPHC_SDMMC4,

    /* 16 */
    NONE(TCW),
    PERIPHC_PWM,
    PERIPHC_I2S2,
    NONE(RESERVED19),
    PERIPHC_VI,
    NONE(RESERVED21),
    NONE(USBD),
    NONE(ISP),

    /* 24 */
    NONE(RESERVED24),
    NONE(RESERVED25),
    PERIPHC_DISP2,
    PERIPHC_DISP1,
    PERIPHC_HOST1X,
    NONE(VCP),
    PERIPHC_I2S0,
    NONE(CACHE2),

    /* Middle word: 63:32 */
    NONE(MEM),
    NONE(AHBDMA),
    NONE(APBDMA),
    NONE(RESERVED35),
    NONE(RESERVED36),
    NONE(STAT_MON),
    NONE(RESERVED38),
    NONE(FUSE),

    /* 40 */
    NONE(KFUSE),
    PERIPHC_SBC1,       /* SBCx = SPIx */
    PERIPHC_NOR,
    NONE(RESERVED43),
    PERIPHC_SBC2,
    NONE(XIO),
    PERIPHC_SBC3,
    PERIPHC_I2C5,

    /* 48 */
    NONE(DSI),
    NONE(RESERVED49),
    PERIPHC_HSI,
    PERIPHC_HDMI,
    NONE(CSI),
    NONE(RESERVED53),
    PERIPHC_I2C2,
    PERIPHC_UART3,

    /* 56 */
    NONE(MIPI_CAL),
    PERIPHC_EMC,
    NONE(USB2),
    NONE(USB3),
    NONE(RESERVED60),
    PERIPHC_VDE,
    NONE(BSEA),
    NONE(BSEV),

    /* Upper word 95:64 */
    NONE(RESERVED64),
    PERIPHC_UART4,
    PERIPHC_UART5,
    PERIPHC_I2C3,
    PERIPHC_SBC4,
    PERIPHC_SDMMC3,
    NONE(PCIE),
    PERIPHC_OWR,

    /* 72 */
    NONE(AFI),
    PERIPHC_CSITE,
    NONE(PCIEXCLK),
    NONE(AVPUCQ),
    NONE(LA),
    NONE(TRACECLKIN),
    NONE(SOC_THERM),
    NONE(DTV),

    /* 80 */
    NONE(RESERVED80),
    PERIPHC_I2CSLOW,
    NONE(DSIB),
    PERIPHC_TSEC,
    NONE(RESERVED84),
    NONE(RESERVED85),
    NONE(RESERVED86),
    NONE(EMUCIF),

    /* 88 */
    NONE(RESERVED88),
    NONE(XUSB_HOST),
    NONE(RESERVED90),
    PERIPHC_MSENC,
    NONE(RESERVED92),
    NONE(RESERVED93),
    NONE(RESERVED94),
    NONE(XUSB_DEV),

    /* V word: 31:0 */
    NONE(CPUG),
    NONE(CPULP),
    NONE(V_RESERVED2),
    PERIPHC_MSELECT,
    NONE(V_RESERVED4),
    PERIPHC_I2S3,
    PERIPHC_I2S4,
    PERIPHC_I2C4,

    /* 104 */
    PERIPHC_SBC5,
    PERIPHC_SBC6,
    PERIPHC_AUDIO,
    NONE(APBIF),
    PERIPHC_DAM0,
    PERIPHC_DAM1,
    PERIPHC_DAM2,
    PERIPHC_HDA2CODEC2X,

    /* 112 */
    NONE(ATOMICS),
    NONE(V_RESERVED17),
    NONE(V_RESERVED18),
    NONE(V_RESERVED19),
    NONE(V_RESERVED20),
    NONE(V_RESERVED21),
    NONE(V_RESERVED22),
    PERIPHC_ACTMON,

    /* 120 */
    NONE(EXTPERIPH1),
    NONE(EXTPERIPH2),
    NONE(EXTPERIPH3),
    NONE(OOB),
    PERIPHC_SATA,
    PERIPHC_HDA,
    NONE(TZRAM),
    NONE(SE),

    /* W word: 31:0 */
    NONE(HDA2HDMICODEC),
    NONE(SATACOLD),
    NONE(W_RESERVED2),
    NONE(W_RESERVED3),
    NONE(W_RESERVED4),
    NONE(W_RESERVED5),
    NONE(W_RESERVED6),
    NONE(W_RESERVED7),

    /* 136 */
    NONE(CEC),
    NONE(W_RESERVED9),
    NONE(W_RESERVED10),
    NONE(W_RESERVED11),
    NONE(W_RESERVED12),
    NONE(W_RESERVED13),
    NONE(XUSB_PADCTL),
    NONE(W_RESERVED15),

    /* 144 */
    NONE(W_RESERVED16),
    NONE(W_RESERVED17),
    NONE(W_RESERVED18),
    NONE(W_RESERVED19),
    NONE(W_RESERVED20),
    NONE(ENTROPY),
    NONE(DDS),
    NONE(W_RESERVED23),

    /* 152 */
    NONE(DP2),
    NONE(AMX0),
    NONE(ADX0),
    NONE(DVFS),
    NONE(XUSB_SS),
    NONE(W_RESERVED29),
    NONE(W_RESERVED30),
    NONE(W_RESERVED31),

    /* X word: 31:0 */
    NONE(SPARE),
    NONE(X_RESERVED1),
    NONE(X_RESERVED2),
    NONE(X_RESERVED3),
    NONE(CAM_MCLK),
    NONE(CAM_MCLK2),
    PERIPHC_I2C6,
    NONE(X_RESERVED7),

    /* 168 */
    NONE(X_RESERVED8),
    NONE(X_RESERVED9),
    NONE(X_RESERVED10),
    NONE(VIM2_CLK),
    NONE(X_RESERVED12),
    NONE(X_RESERVED13),
    NONE(EMC_DLL),
    NONE(X_RESERVED15),

    /* 176 */
    NONE(HDMI_AUDIO),
    NONE(CLK72MHZ),
    NONE(VIC),
    NONE(X_RESERVED19),
    NONE(ADX1),
    NONE(DPAUX),
    NONE(SOR0),
    NONE(X_RESERVED23),

    /* 184 */
    NONE(GPU),
    NONE(AMX1),
    NONE(X_RESERVED26),
    NONE(X_RESERVED27),
    NONE(X_RESERVED28),
    NONE(X_RESERVED29),
    NONE(X_RESERVED30),
    NONE(X_RESERVED31),
};

//47 52 99

/* Returns  the clock source register for a peripheral */
unsigned int get_periph_source_reg(int periph_id) {
    enum periphc_internal_id internal_id;

    /* Coresight is a special case */
    if (periph_id == 52)
        return (0x60006000 + 0x100 + ((52+1) * 4));

    internal_id = periph_id_to_internal_id[periph_id];  // array
    if (internal_id >= 0x40) {
        internal_id -= 0x40;
        return (0x60006000 + 0x3B0 + (internal_id * 4));
    } else {
        return (0x60006000 + 0x100 + (internal_id * 4));
    }
}

void clock_ll_set_source_divisor(int periph_id, unsigned source, unsigned divisor) {
    unsigned int reg = get_periph_source_reg(periph_id);
    unsigned int value;

    value = (*(volatile unsigned int *) (reg));

    value &= ~(3U << 30);
    value |= source << 30;

    value &= ~(0xFFFF << 0);
    value |= divisor << 0;

    (*(volatile unsigned int *) (reg)) = value;
}

void reset_set_enable(int periph_id, int enable) {
    unsigned int reset;
    unsigned int reg;

    /* Enable/disable reset to the peripheral */
    if (periph_id < 96)
        reset = 0x60006000 + 0x4 + (((periph_id < 96) ? ((periph_id) >> 5) : ((periph_id - 96) >> 5)) * 4);
    else
        reset = 0x60006000 + 0x358 + (((periph_id < 96) ? ((periph_id) >> 5) : ((periph_id - 96) >> 5)) * 4);
    reg = (*(volatile unsigned int *) (reset));
    if (enable)
        reg |= (1 << ((periph_id) & 0x1f));
    else
        reg &= ~(1 << ((periph_id) & 0x1f));
    (*(volatile unsigned int *) (reset)) = reg;
}

void tegra_i2c_ll_write_addr(unsigned int addr, unsigned int config)
{

    (*(volatile unsigned int *) (0x70000000 + 0xD000 + 0x4)) = addr;
    (*(volatile unsigned int *) (0x70000000 + 0xD000 + 0x0)) = config;
}

void tegra_i2c_ll_write_data(unsigned int data, unsigned int config)
{
    (*(volatile unsigned int *) (0x70000000 + 0xD000 + 0xC)) = data;
    (*(volatile unsigned int *) (0x70000000 + 0xD000 + 0x0)) = config;
}

/* AS3722-PMIC-specific early init code - get CPU rails up, etc */
void pmic_enable_cpu_vdd(void) {
    /* Don't need to set up VDD_CORE - already done - by OTP */

    // Setting VDD_CPU to 1.0V via AS3722 reg
    /*
     * Bring up VDD_CPU via the AS3722 PMIC on the PWR I2C bus.
     * First set VDD to 1.0V, then enable the VDD regulator.
     */
    tegra_i2c_ll_write_addr(0x80, 2);
    tegra_i2c_ll_write_data((0x3C00 | 0x00), 0xA02);
    /*
     * Don't write SDCONTROL - it's already 0x7F, i.e. all SDs enabled.
     * tegra_i2c_ll_write_data(AS3722_SD0CONTROL_DATA, I2C_SEND_2_BYTES);
     */
    udelay(10 * 1000);

    /*
     * Bring up VDD_GPU via the AS3722 PMIC on the PWR I2C bus.
     * First set VDD to 1.0V, then enable the VDD regulator.
     */
    tegra_i2c_ll_write_addr(0x80, 2);
    tegra_i2c_ll_write_data((0x2800 | 0x06), 0xA02);
    /*
     * Don't write SDCONTROL - it's already 0x7F, i.e. all SDs enabled.
     * tegra_i2c_ll_write_data(AS3722_SD6CONTROL_DATA, I2C_SEND_2_BYTES);
     */
    udelay(10 * 1000);

    /*
     * Bring up VPP_FUSE via the AS3722 PMIC on the PWR I2C bus.
     * First set VDD to 1.2V, then enable the VDD regulator.
     */
    tegra_i2c_ll_write_addr(0x80, 2);
    tegra_i2c_ll_write_data((0x1000 | 0x12), 0xA02);
    /*
     * Don't write LDCONTROL - it's already 0xFF, i.e. all LDOs enabled.
     * tegra_i2c_ll_write_data(AS3722_LDO2CONTROL_DATA, I2C_SEND_2_BYTES);
     */
    udelay(10 * 1000);

    /*
     * Bring up VDD_SDMMC via the AS3722 PMIC on the PWR I2C bus.
     * First set it to bypass 3.3V straight thru, then enable the regulator
     *
     * NOTE: We do this early because doing it later seems to hose the CPU
     * power rail/partition startup. Need to debug.
     */
    tegra_i2c_ll_write_addr(0x80, 2);
    tegra_i2c_ll_write_data((0x3F00 | 0x16), 0xA02);
    /*
     * Don't write LDCONTROL - it's already 0xFF, i.e. all LDOs enabled.
     * tegra_i2c_ll_write_data(AS3722_LDO6CONTROL_DATA, I2C_SEND_2_BYTES);
     */
    udelay(10 * 1000);
}

static void enable_cpu_power_rail(void) {
    /* un-tristate PWR_I2C SCL/SDA, rest of the defaults are correct */
    (*(volatile unsigned int *) (0x70000000 + (0x3000 + ((173) * 4)))) &= ~(1 << 4);
    (*(volatile unsigned int *) (0x70000000 + (0x3000 + ((174) * 4)))) &= ~(1 << 4);

    pmic_enable_cpu_vdd();

    /*
     * Set CPUPWRGOOD_TIMER - APB clock is 1/2 of SCLK (102MHz),
     * set it for 5ms as per SysEng (102MHz*5ms = 510000 (7C830h).
     */
    (*(volatile unsigned int *) (0x7000E400 + 0xC8)) = 0x7C830;

    /* Set polarity to 0 (normal) and enable CPUPWRREQ_OE */
    (*(volatile unsigned int *) (0x7000E400)) &= ~(1 << 15);
    (*(volatile unsigned int *) (0x7000E400)) |= (1 << 16);
}

/* CLK_RST_CONTROLLER_CLK_CPU_CMPLX_CLR 0x34c */
#define CLR_CPU0_CLK_STP        (1 << 8)
#define CLR_CPU1_CLK_STP        (1 << 9)
#define CLR_CPU2_CLK_STP        (1 << 10)
#define CLR_CPU3_CLK_STP        (1 << 11)

static void enable_cpu_clocks(void) {
    unsigned int reg;

    /* Wait for PLL-X to lock */
    do {
        reg = (*(volatile unsigned int *) (0x60006000 + 0xE0));
    } while ((reg & (1U << 27)) == 0);

    /* Wait until all clocks are stable */
    udelay(1000);

    // Setting CCLK_BURST and DIVIDER
    (*(volatile unsigned int *) (0x60006000 + 0x20)) = 0x20008888;
    (*(volatile unsigned int *) (0x60006000 + 0x24)) = 0x80000000;

    /* Enable the clock to all CPUs */
    reg = CLR_CPU3_CLK_STP | CLR_CPU2_CLK_STP | CLR_CPU1_CLK_STP
            | CLR_CPU0_CLK_STP;
    (*(volatile unsigned int *) (0x60006000 + 0x34C)) = reg;

    /* Always enable the main CPU complex clocks */
    clock_set_enable(0, 1);
    clock_set_enable(97, 1);
    clock_set_enable(96, 1);
}

void clock_enable_coresight(int enable) {
    unsigned int rst, src = 2;

    clock_set_enable(73, enable);
    reset_set_enable(73, !enable);

    if (enable) {
        /*
         * Put CoreSight on PLLP_OUT0 and divide it down as per
         * PLLP base frequency based on SoC type (T20/T30+).
         * Clock divider request would setup CSITE clock as 144MHz
         * for PLLP base 216MHz and 204MHz for PLLP base 408MHz
         */
        src = ((((408000) * 2) / 204000) - 2);
        clock_ll_set_source_divisor(52, 0, src);

        /* Unlock the CPU CoreSight interfaces */
        rst = 0xC5ACCE55;
        (*(volatile unsigned int *) (0x70800000 + 0x10FB0)) = rst;
        (*(volatile unsigned int *) (0x70800000 + 0x12FB0)) = rst;
        (*(volatile unsigned int *) (0x70800000 + 0x14FB0)) = rst;
        (*(volatile unsigned int *) (0x70800000 + 0x16FB0)) = rst;
    }
}

/* CLK_RST_CONTROLLER_RST_CPUxx_CMPLX_CLR 0x344 */
#define CLR_CPURESET0           (1 << 0)
#define CLR_CPURESET1           (1 << 1)
#define CLR_CPURESET2           (1 << 2)
#define CLR_CPURESET3           (1 << 3)
#define CLR_DBGRESET0           (1 << 12)
#define CLR_DBGRESET1           (1 << 13)
#define CLR_DBGRESET2           (1 << 14)
#define CLR_DBGRESET3           (1 << 15)
#define CLR_CORERESET0          (1 << 16)
#define CLR_CORERESET1          (1 << 17)
#define CLR_CORERESET2          (1 << 18)
#define CLR_CORERESET3          (1 << 19)
#define CLR_CXRESET0            (1 << 20)
#define CLR_CXRESET1            (1 << 21)
#define CLR_CXRESET2            (1 << 22)
#define CLR_CXRESET3            (1 << 23)
#define CLR_L2RESET         (1 << 24)
#define CLR_NONCPURESET         (1 << 29)
#define CLR_PRESETDBG           (1 << 30)

static void remove_cpu_resets(void) {
    /* Take the slow and fast partitions out of reset */
    (*(volatile unsigned int *) (0x60006000 + 0x45C)) = (1 << 29);
    (*(volatile unsigned int *) (0x60006000 + 0x454)) = (1 << 29);

    /* Clear the SW-controlled reset of the slow cluster */
    (*(volatile unsigned int *) (0x60006000 + 0x45C)) = CLR_CPURESET0 | CLR_DBGRESET0 | CLR_CORERESET0 | CLR_CXRESET0
            | CLR_L2RESET | CLR_PRESETDBG;

    /* Clear the SW-controlled reset of the fast cluster */
    (*(volatile unsigned int *) (0x60006000 + 0x454)) = CLR_CPURESET0 | CLR_DBGRESET0 | CLR_CORERESET0 | CLR_CXRESET0
            | CLR_CPURESET1 | CLR_DBGRESET1 | CLR_CORERESET1 | CLR_CXRESET1
            | CLR_CPURESET2 | CLR_DBGRESET2 | CLR_CORERESET2 | CLR_CXRESET2
            | CLR_CPURESET3 | CLR_DBGRESET3 | CLR_CORERESET3 | CLR_CXRESET3
            | CLR_L2RESET | CLR_PRESETDBG;;
}

static int is_partition_powered(unsigned int partid) {
    /* Get power gate status */
    unsigned int reg = (*(volatile unsigned int *) (0x70000000 + 0xE400 + 0x38));
    return !!(reg & (1 << partid));
}

static void power_partition(unsigned int partid) {
    /* Is the partition already on? */
    if (!is_partition_powered(partid)) {
        /* No, toggle the partition power state (OFF -> ON) */
        (*(volatile unsigned int *) (0x70000000 + 0xE400 + 0x30)) = (1 << 8)
                | partid;

        /* Wait for the power to come up */
        while (!is_partition_powered(partid))
            ;

        /* Give I/O signals time to stabilize */
        udelay(1000);
    }
}

void tegra124_init_clocks(void) {

    (*(volatile unsigned int *) (0x60007000 + 0x2C)) &= ~(1 << 0); // Set active CPU cluster to G

    /* Change the oscillator drive strength */
    unsigned int val = (*(volatile unsigned int *) (0x60006000 + 0x50));
    val &= ~(0x3F << 4);
    val |= (7 << 4);
    (*(volatile unsigned int *) (0x60006000 + 0x50)) = val;

    /* Update same value in PMC_OSC_EDPD_OVER XOFS field for warmboot */
    val = (*(volatile unsigned int *) (0x70000000 + 0xE400 + 0x1A4));
    val &= ~(0x3F << 1);
    val |= (7 << 1);
    (*(volatile unsigned int *) (0x70000000 + 0xE400 + 0x1A4)) = val;

    (*(volatile unsigned int *) (0x70000000 + 0xE400 + 0x440)) |= (1 << 12);/* Set HOLD_CKE_LOW_EN to 1 */

//init_pllx>----------------------
    /* If PLLX is already enabled, just return */
    if ((*(volatile unsigned int *) (0x600060e0 + 0x0)) & ((1U << 30))) {
        return;
    }

    /* Disable IDDQ */
    (*(volatile unsigned int *) (0x60006000 + 0x518)) &= ~(1U << 3);

    udelay(2);

    /* Set BYPASS, m, n and p to PLLX_BASE */
    unsigned int reg = (1U << 31) | (1 << 0);
    reg |= ((116 << 8) | (1 << 20));
    (*(volatile unsigned int *) (0x600060e0)) = reg;

    /* Set cpcon to PLLX_MISC */
    reg = 0;

    /* Set dccon to PLLX_MISC if freq > 600MHz */
    if (116 > 600)
        reg |= (1 << 20);
    (*(volatile unsigned int *) (0x600060e4)) = reg;

    /* Disable BYPASS */
    (*(volatile unsigned int *) (0x600060e0)) &= ~(1U << 31);
    /* Set lock_enable to PLLX_MISC */
    (*(volatile unsigned int *) (0x600060e4)) |= (1U << 18);
    /* Enable PLLX last, once it's all configured */
    (*(volatile unsigned int *) (0x600060e0)) |= (1U << 30);
//<init_pllx---------------------

    (*(volatile unsigned int *) (0x60006000 + 0x30)) = (1 << 4);

    /* Enable clocks to required peripherals. TBD - minimize this list */
    clock_set_enable(31, 1);
    clock_set_enable(8, 1);
    clock_set_enable(5, 1);
    clock_set_enable(0, 1);
    clock_set_enable(57, 1);
    clock_set_enable(47, 1);
    clock_set_enable(34, 1);
    clock_set_enable(32, 1);
    clock_set_enable(73, 1);
    clock_set_enable(99, 1);
    clock_set_enable(155, 1);

    /*
     * Set MSELECT clock source as PLLP (00), and ask for a clock
     * divider that would set the MSELECT clock at 102MHz for a
     * PLLP base of 408MHz.
     */
    clock_ll_set_source_divisor(99, 0, ((((408000) * 2) / 102000) - 2));
    udelay(1000); /* Give clock time to stabilize */
    clock_ll_set_source_divisor(47, 3, 16); /* I2C5 (DVC) gets CLK_M and a divisor of 17 */
    udelay(1000); /* Give clock time to stabilize */

    /* Take required peripherals out of reset */
    reset_set_enable(31, 0);
    reset_set_enable(8, 0);
    reset_set_enable(5, 0);
    reset_set_enable(1, 0);
    reset_set_enable(57, 0);
    reset_set_enable(47, 0);
    reset_set_enable(34, 0);
    reset_set_enable(32, 0);
    reset_set_enable(73, 0);
    reset_set_enable(99, 0);
    reset_set_enable(155, 0);
}

void start_cpu(unsigned int reset_vector) {
    tegra124_init_clocks();
    /* Set power-gating timer multiplier */

    (*(volatile unsigned int *) (0x70000000 + 0xE400 + 0x1E4)) = (3 << 0) | (3 << 3);
    enable_cpu_power_rail();
    enable_cpu_clocks();
    clock_enable_coresight(1);
    remove_cpu_resets();
    (*(volatile unsigned int *) (0x6000F000 + 0x100)) = reset_vector;

    /* Power up the fast cluster rail partition */
    power_partition(0);
    /* Power up the fast cluster non-CPU partition */
    power_partition(15);
    /* Power up the fast cluster CPU0 partition */
    power_partition(14);

    /* Power up the fast cluster CPU1 partition */
    //power_partition(9);
    /* Power up the fast cluster CPU2 partition */
    //power_partition(10);
    /* Power up the fast cluster CPU3 partition */
    //power_partition(11);
}

void spin() {
    for (;;) {
        ;
    }
}

int main(void) {
    void (*fp)();
    fp = &spin;
    start_cpu((unsigned int)fp);
    return 0;
}
