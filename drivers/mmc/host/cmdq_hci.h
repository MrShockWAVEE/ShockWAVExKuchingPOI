/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef LINUX_MMC_CQ_HCI_H
#define LINUX_MMC_CQ_HCI_H
#include <linux/mmc/core.h>
#include <mt-plat/sync_write.h>
#include <linux/platform_device.h>

/* registers */
/* version */
#define CQVER      0x00

/* capabilities */
#define CQCAP      0x04

/* configuration */
#define CQCFG      0x08
#define CQ_DCMD	         0x00001000
#define CQ_TASK_DESC_SZ  0x00000100
#define CQ_ENABLE        0x00000001
#define CQ_CRYPTO_ENABLE 0x00000002

/* control */
#define CQCTL      0x0C
#define CLEAR_ALL_TASKS  0x00000100
#define HALT             0x00000001

/* interrupt status */
#define CQIS       0x10
#define CQIS_HAC         (1 << 0)
#define CQIS_TCC         (1 << 1)
#define CQIS_RED         (1 << 2)
#define CQIS_TCL         (1 << 3)

/* interrupt status enable */
#define CQISTE     0x14

/* interrupt signal enable */
#define CQISGE     0x18

/* interrupt coalescing */
#define CQIC       0x1C
#define CQIC_ENABLE      (1 << 31)
#define CQIC_RESET       (1 << 16)
#define CQIC_ICCTHWEN    (1 << 15)
#define CQIC_ICCTH(x)    ((x & 0x1F) << 8)
#define CQIC_ICTOVALWEN  (1 << 7)
#define CQIC_ICTOVAL(x)  (x & 0x7F)

/* task list base address */
#define CQTDLBA	   0x20

/* task list base address upper */
#define CQTDLBAU   0x24

/* door-bell */
#define CQTDBR     0x28

/* task completion notification */
#define CQTCN      0x2C

/* device queue status */
#define CQDQS      0x30

/* device pending tasks */
#define CQDPT      0x34

/* task clear */
#define CQTCLR     0x38

/* send status config 1 */
#define CQSSC1     0x40
/*
 * Value n means CQE would send CMD13 during the transfer of data block
 * BLOCK_CNT-n
 */
#define SEND_QSR_INTERVAL 0x70000

/* send status config 2 */
#define CQSSC2     0x44

/* response for dcmd */
#define CQCRDCT    0x48

/* response mode error mask */
#define CQRMEM		0x50
#define CQ_EXCEPTION	(1 << 6)

/* task error info */
#define CQTERRI		0x54

/* CQTERRI bit fields */
#define CQ_RMECI	0x1F
#define CQ_RMETI	(0x1F << 8)
#define CQ_RMEFV	(1 << 15)
#define CQ_DTECI	(0x3F << 16)
#define CQ_DTETI	(0x1F << 24)
#define CQ_DTEFV	(1 << 31)

#define GET_CMD_ERR_CMDIDX(__r__) (__r__ & CQ_RMECI)
#define GET_CMD_ERR_TAG(__r__) ((__r__ & CQ_RMETI) >> 8)
#define GET_DAT_ERR_TAG(__r__) ((__r__ & CQ_DTETI) >> 24)

/* command response index */
#define CQCRI      0x58

/* command response argument */
#define CQCRA      0x5C

#define CRNQP      0x70
#define CRNQDUN    0x74
#define CRNQIS     0x78
#define CRNQIE     0x7C

#define CRCAP      0x100
#define	CRCAP_CFGPTR (0xffUL	<< 24) /* RO */

#define CQ_INT_ALL 0xF
#define CQIC_DEFAULT_ICCTH 31
#define CQIC_DEFAULT_ICTOVAL 1

/* attribute fields */
#define VALID(x)	((x & 1) << 0)
#define END(x)		((x & 1) << 1)
#define INT(x)		((x & 1) << 2)
#define ACT(x)		((x & 0x7) << 3)

/* data command task descriptor fields */
#define FORCED_PROG(x) ((x & 1) << 6)
#define CONTEXT(x)     ((x & 0xF) << 7)
#define DATA_TAG(x)    ((x & 1) << 11)
#define DATA_DIR(x)    ((x & 1) << 12)
#define PRIORITY(x)    ((x & 1) << 13)
#define QBAR(x)	       ((x & 1) << 14)
#define REL_WRITE(x)   ((x & 1) << 15)
#define BLK_COUNT(x)   ((x & 0xFFFF) << 16)
#define BLK_ADDR(x)	   ((x & 0xFFFFFFFF) << 32)

#define DUN(x)         ((x & 0xFFFFFFFF) << 0)
#define CCI(x)         ((x & 0xFF) << 32)
#define TRAN(x)        ((x & 0x3LL) << 40)
#define CE(x)          ((x & 0x7LL) << 47)

/* direct command task descriptor fields */
#define CMD_INDEX(x)   ((x & 0x3F) << 16)
#define CMD_TIMING(x)  ((x & 1) << 22)
#define RESP_TYPE(x)   ((x & 0x3) << 23)

/* transfer descriptor fields */
#define DAT_LENGTH(x)  ((x & 0xFFFF) << 16)
#define DAT_ADDR_LO(x) ((x & 0xFFFFFFFF) << 32)
#define DAT_ADDR_HI(x) ((x & 0xFFFFFFFF) << 0)

#define CQ_VENDOR_CFG	0x100
#define CMDQ_SEND_STATUS_TRIGGER (1 << 31)

#define CQ_TASK_DESC_TASK_PARAMS_SIZE 8
#define CQ_TASK_DESC_CE_PARAMS_SIZE 8

/*--------------------------------------------------------------------------*/
/* Crypto CQE                                                    */
/*--------------------------------------------------------------------------*/
/* capabilities */
#define CQHCI_CAP			0x04
#define CQHCI_CAP_CS			(1 << 28)
#define CQHCI_CCAP			0x100
#define CQHCI_CRYPTOCAP			0x104

/* configuration */
#define CQHCI_CRYPTO_ENABLE		0x00000002

#define CQHCI_TASK_DESC_SZ_128		0x1

/* CCAP - Crypto Capability 100h */
union cqhci_crypto_capabilities {
	__le32 reg_val;
	struct {
		u8 num_crypto_cap;
		u8 config_count;
		u8 reserved;
		u8 config_array_ptr;
	};
};

enum cqhci_crypto_key_size {
	CQHCI_CRYPTO_KEY_SIZE_INVALID	= 0,
	CQHCI_CRYPTO_KEY_SIZE_128	= 1,
	CQHCI_CRYPTO_KEY_SIZE_192	= 2,
	CQHCI_CRYPTO_KEY_SIZE_256	= 3,
	CQHCI_CRYPTO_KEY_SIZE_512	= 4,
};

enum cqhci_crypto_alg {
	CQHCI_CRYPTO_ALG_AES_XTS		= 0,
	CQHCI_CRYPTO_ALG_BITLOCKER_AES_CBC	= 1,
	CQHCI_CRYPTO_ALG_AES_ECB		= 2,
	CQHCI_CRYPTO_ALG_ESSIV_AES_CBC		= 3,
};

/* x-CRYPTOCAP - Crypto Capability X */
union cqhci_crypto_cap_entry {
	__le32 reg_val;
	struct {
		u8 algorithm_id;
		u8 sdus_mask; /* Supported data unit size mask */
		u8 key_size;
		u8 reserved;
	};
};

#define CQHCI_CRYPTO_CONFIGURATION_ENABLE (1 << 7)
#define CQHCI_CRYPTO_KEY_MAX_SIZE 64
/* x-CRYPTOCFG - Crypto Configuration X */
union cqhci_crypto_cfg_entry {
	__le32 reg_val[32];
	struct {
		u8 crypto_key[CQHCI_CRYPTO_KEY_MAX_SIZE];
		/* 4KB/512 = 8 */
		u8 data_unit_size;
		u8 crypto_cap_idx;
		u8 reserved_1;
		u8 config_enable;
		u8 reserved_multi_host;
		u8 reserved_2;
		u8 vsb[2];
		u8 reserved_3[56];
	};
};

struct cmdq_host {
	const struct cmdq_host_ops *ops;
	void __iomem *mmio;
	struct mmc_host *mmc;
	void __iomem	*base;	/* host base address */

	/* 64 bit DMA */
	bool dma64;
	int num_slots;

	u32 dcmd_slot;
	u32 caps;
#define CMDQ_TASK_DESC_SZ_128 0x1
#define CMDQ_CAP_CRYPTO_SUPPORT 0x2

	u32 quirks;
#define CMDQ_QUIRK_SHORT_TXFR_DESC_SZ 0x1
#define CMDQ_QUIRK_NO_DCMD 0x2
#define CMDQ_QUIRK_PRIO_READ (1<<2)

	bool enabled;
	bool halted;
	bool init_done;

	u8 *desc_base;

	/* total descriptor size */
	u8 slot_sz;

	/* 64/128 bit depends on CQCFG */
	u8 task_desc_len;

	/* 64 bit on 32-bit arch, 128 bit on 64-bit */
	u8 link_desc_len;

	u8 *trans_desc_base;
	/* same length as transfer descriptor */
	u8 trans_desc_len;

	dma_addr_t desc_dma_base;
	dma_addr_t trans_desc_dma_base;

	struct completion halt_comp;
	struct mmc_request **mrq_slot;
	void *private;
#ifdef CONFIG_MMC_CRYPTO
	union cqhci_crypto_capabilities crypto_capabilities;
	union cqhci_crypto_cap_entry *crypto_cap_array;
	union cqhci_crypto_cfg_entry *crypto_cfgs;
	u32 crypto_cfg_register;
#endif
};

struct cmdq_host_ops {
	void (*set_transfer_params)(struct mmc_host *mmc);
	void (*set_data_timeout)(struct mmc_host *mmc, u32 val);
	void (*clear_set_irqs)(struct mmc_host *mmc, bool clear);
	void (*set_block_size)(struct mmc_host *mmc);
	void (*dump_vendor_regs)(struct mmc_host *mmc);
	void (*write_l)(struct cmdq_host *host, u32 val, int reg);
	u32 (*read_l)(struct cmdq_host *host, int reg);
	void (*clear_set_dumpregs)(struct mmc_host *mmc, bool set);
	void (*enhanced_strobe_mask)(struct mmc_host *mmc, bool set);
	int (*reset)(struct mmc_host *mmc);
	int (*crypto_cfg)(struct mmc_host *mmc, struct mmc_request *mrq,
		u32 slot, u64 *hci_ce_ctx);
	void (*crypto_cfg_reset)(struct mmc_host *mmc, unsigned int slot);
	void (*post_cqe_halt)(struct mmc_host *mmc);
	void (*pre_cqe_enable)(struct mmc_host *mmc, bool en);
	int (*pre_irq_complete)(struct mmc_host *mmc, unsigned int err);
};

static inline void cmdq_writel(struct cmdq_host *host, u32 val, int reg)
{
	writel_relaxed(val, host->mmio + reg);
}

static inline u32 cmdq_readl(struct cmdq_host *host, int reg)
{
	return readl_relaxed(host->mmio + reg);
}

static inline void cmdq_writel_normal(struct cmdq_host *host, u32 val, int reg)
{
	writel_relaxed(val, host->mmio - 0x800 + reg);
}

static inline u32 cmdq_readl_normal(struct cmdq_host *host, int reg)
{
	return readl_relaxed(host->mmio - 0x800 + reg);
}

static inline void cmdq_clear_normal(struct cmdq_host *host, u32 val, int reg)
{
	unsigned int tv = cmdq_readl_normal(host, reg);

	tv &= ~((u32)(val));
	cmdq_writel_normal(host, tv, reg);
}

extern irqreturn_t cmdq_irq(struct mmc_host *mmc, int err);
extern int cmdq_init(struct cmdq_host *cq_host, struct mmc_host *mmc,
		     bool dma64);
extern struct cmdq_host *cmdq_pltfm_init(struct platform_device *pdev);
extern void cmdq_dumpregs(struct cmdq_host *cq_host);

#ifdef CONFIG_MTK_EMMC_HW_CQ
static inline u8 *get_desc(struct cmdq_host *cq_host, u8 tag)
{
	return cq_host->desc_base + (tag * cq_host->slot_sz);
}
#else
static inline u8 *get_desc(struct cmdq_host *cq_host, u8 tag)
{
	return NULL;
}
#endif

#endif
